/**
* Implementation of the Statistical Region Merging Algorithm
*/

use opencv::{
    core::Mat,
    core::CV_32F,
    core::CV_8U,
    core::Vec3f,
    core::VecN,
    core::Vector,
    prelude::MatTrait,
    prelude::MatTraitConst,
    imgcodecs::imwrite,
};

use std::path::Path;


pub struct SRM<'a> {
    q: i32,
    g: i32,
    delta: f32,
    img_size: i32,
    min_size: f32,
    max_regions: i32,
    img_rows: i32,
    img_cols: i32,
    rank: Vec<i32>,
    parent: Vec<i32>,
    img: &'a Mat,
    reshaped_image: Mat,
}



impl<'a> SRM<'a> {

    pub fn new(q: i32, max_regions: i32, min_size: f32, img: &'a Mat) -> Result<Self, opencv::Error> {

        let img_size: i32 = img.rows() * img.cols();
        let delta: f32 = f32::ln(6.0) + 2.0 * f32::ln(img_size as f32);
        let min_size: f32 = min_size * img_size as f32;

        Ok(
            SRM {
                q,
                g: 256,
                delta,
                img_size,
                min_size,
                max_regions,
                img_rows: img.rows(),
                img_cols: img.cols(),
                rank: vec![1; img_size as usize],
                parent: (0..img_size as i32).collect(),
                img,
                reshaped_image: Mat::default(),
            }
        )
    }


    pub fn run(&mut self) -> Result<(), Box<dyn std::error::Error>> {

        let mut float_image = Mat::default();
        self.img.convert_to(&mut float_image, CV_32F, 1.0, 0.0)?;
        let reshaped_img = float_image.reshape_mut(3, self.img_size)?.try_clone()?;
        self.reshaped_image = reshaped_img;


        // 1) Sort the list of pairs (4-Connected Neighbors)
        let edge_list: Vec<(i32, i32)> = self.make_edge_pair_list();

        // // 2) Iterate through the list of pairs and perform the statistical test
        for p in &edge_list {
            let parent_a = self.get_parent(p.0);
            let parent_b = self.get_parent(p.1);

            if parent_a != parent_b && self.predicate(parent_a, parent_b) {
                let _ = self.merge(parent_a, parent_b);
            }
        }

        // 3) Merge Occlusions if present
        if self.max_regions > 0 {
            self.merge_occlusions();
        }

        // 4) Prepare the segmented image's colors
        let _ = self.process_image();

        // 5) Reshape and re-convert the image
        let original_shape_image = self.reshaped_image
        .reshape(3, self.img_rows)?
        .try_clone()?;
        original_shape_image.convert_to(&mut self.reshaped_image, CV_8U, 1.0, 0.0)?;


        Ok(())

    }

    pub fn make_edge_pair_list(&self) -> Vec<(i32, i32)> {

        let mut edge_list = Vec::new();
        let rows = self.img_rows;
        let cols = self.img_cols;

        for i in 0..rows {
            for j in 0..cols {
                let index = i * rows + j;
                // Add vertical edge (index -> index + cols)
                if i != rows - 1 {
                    edge_list.push((index, index + cols));
                }
                // Add horizontal edge (index -> index + 1)
                if j != cols - 1 {
                    edge_list.push((index, index + 1));
                }
            }
        }

        self.sort_edge_pairs(&mut edge_list);

        edge_list
    }

    pub fn sort_edge_pairs(&self, edge_pairs: &mut Vec<(i32, i32)>) {
        edge_pairs.sort_by(|a, b| {
            a.0.cmp(&b.0).then_with(|| a.1.cmp(&b.1))
        });
    }

    pub fn evaluate_predicate(&self, parent_a: i32) -> f32 {
        ((self.g.pow(2) as f32) / (2.0 * self.q as f32 * self.rank[parent_a as usize] as f32))
        * (self.g as f32).min(self.rank[parent_a as usize] as f32)
        * ((self.rank[parent_a as usize] as f32) + 1.0).ln()
        + self.delta
    }


    pub fn predicate(&mut self, parent_a: i32, parent_b: i32) -> bool {

        let predicate_a = self.evaluate_predicate(parent_a);
        let predicate_b = self.evaluate_predicate(parent_b);


        let pixel_a = self.reshaped_image.at::<Vec3f>(parent_a as i32).unwrap();
        let pixel_b = self.reshaped_image.at::<Vec3f>(parent_b as i32).unwrap();

        // Computes the squared difference using the .mul() method (quicker)
        let mut comparison = self.subtract_pixels(pixel_a, pixel_b);
        comparison = comparison.mul(comparison);

        self.check_predicate(comparison, predicate_a + predicate_b)

    }

    fn subtract_pixels(
        &self,
        pixel_a: &VecN<f32, 3>,
        pixel_b: &VecN<f32, 3>,
    ) -> VecN<f32, 3> {

        VecN::<f32, 3>::from([
            pixel_a[0] - pixel_b[0],
            pixel_a[1] - pixel_b[1],
            pixel_a[2] - pixel_b[2],
        ])

    }

    fn check_predicate(
        &self,
        squared_diff: Vec3f,
        threshold: f32
    ) -> bool {
        squared_diff[0] < threshold as f32 && squared_diff[1] < threshold as f32 && squared_diff[2] < threshold as f32
    }

    pub fn merge(&mut self, parent_a: i32, parent_b: i32) -> Result<(), Box<dyn std::error::Error>> {


        let sum1 = self.rank[parent_a as usize];
        let sum2 = self.rank[parent_b as usize];


        let pixel_a = *self.reshaped_image.at::<Vec3f>(parent_a)?;
        let pixel_b = *self.reshaped_image.at::<Vec3f>(parent_b)?;


        let color_result = (pixel_a * (sum1 as f32) + pixel_b * (sum2 as f32)) / ((sum1 + sum2) as f32);

        let (parent_a, parent_b) = if sum1 < sum2 {
            (parent_b, parent_a)
        } else {
            (parent_a, parent_b)
        };


        self.parent[parent_b as usize] = parent_a;
        self.rank[parent_a as usize] += self.rank[parent_b as usize];

        *self.reshaped_image.at_mut::<Vec3f>(parent_a)? = color_result;

        Ok(())

    }

    pub fn get_parent(&mut self, parent_a: i32) -> i32 {

        if self.parent[parent_a as usize] == parent_a {
            return parent_a;
        }
        // Lazy propagation
        let p = self.get_parent(self.parent[parent_a as usize]);
        self.parent[parent_a as usize] = p; // Path compression
        p

    }

    pub fn merge_occlusions(&mut self) {

        for i in 1..self.img_size {
            let r1 = self.get_parent(i);
            let r2 = self.get_parent(i - 1);
            if r1 != r2 && (self.rank[r1 as usize] as f32) <= self.min_size {
                let _ = self.merge(r1, r2);
            }
        }

    }

    pub fn process_image(&mut self) -> Result<(), Box<dyn std::error::Error>> {


        for i in 0..self.img_size {

            let parent_idx = self.get_parent(i);
            let color = self.reshaped_image.at::<Vec3f>(parent_idx)?;

            *self.reshaped_image.at_mut::<Vec3f>(i)? = *color;
        }

        Ok(())
    }


    pub fn save_image(&self, abs_path: &str) -> Result<(), Box<dyn std::error::Error>> {

        let base_name = Path::new(abs_path)
        .file_name()
        .and_then(|name| name.to_str())
        .ok_or("Failed to extract base name")?;

        let file_name = format!("Segmented-{}", base_name);
        let params = Vector::<i32>::new();

        imwrite(&file_name, &self.reshaped_image, &params)?;


        Ok(())
    }

}
