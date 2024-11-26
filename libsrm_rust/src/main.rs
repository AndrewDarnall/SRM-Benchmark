/**
 * Rust Implementation of the Statistical Region Merging Algorithm
 * Celebrating 20 years since the paper was published!
 */

use std::env;
use std::process;
use opencv::{Result,imgcodecs};

mod algorithms;

use algorithms::srm::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    
    let cmdline_args: Vec<String> = env::args().collect();

    if cmdline_args.len() != 5 {
        eprintln!("usage:\t{}\t<PATH-TO-IMAGE>\t<Q-Parameter--Default=32>\t<Max-Regions--Default=15>\t<Min-Size--Default=0.001>", cmdline_args[0]);
        process::exit(-1);
    }

    let img = imgcodecs::imread(&cmdline_args[1], imgcodecs::IMREAD_COLOR)?;

    println!(" -- Running the Statistical Region Merging Algorithm on {} -- ", cmdline_args[1]);


    let q: i32 = match cmdline_args[2].parse() {
        Ok(value) => value,
        Err(_) => {
            eprintln!("[Q] must be an integer");
            std::process::exit(1);
        }
    };

    let max_regions: i32 = match cmdline_args[3].parse() {
        Ok(value) => value,
        Err(_) => {
            eprintln!("[max_regions] must be an integer");
            std::process::exit(1);
        }
    };

    let min_size: f32 = match cmdline_args[4].parse() {
        Ok(value) => value,
        Err(_) => {
            eprintln!("[Min Size must be a float]");
            std::process::exit(1);
        }
    };

    // ================================================= //
    let mut srm: SRM = SRM::new(q, max_regions, min_size, &img)?;
    let _ = srm.run()?;
    let _ = srm.save_image(&cmdline_args[1])?;
    // ================================================= //

    println!(" == Finished Running the SRM Algorithm == ");
    Ok(())

}
