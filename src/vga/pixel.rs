#[derive(Copy, Clone)]
pub struct Pixel {
    red: u32,
    green: u32,
    blue: u32,
    alpha: u32,
}

#[derive(Copy, Clone, PartialEq, Eq)]
pub struct Coordinate {
    pub x: usize,
    pub y: usize
}

impl Coordinate {
pub const fn new(x: usize, y: usize) -> Self {
    Self {x,y}
}
}




impl Pixel {
    pub const fn new(red: u32, green: u32, blue: u32, alpha: u32) -> Self {
        Pixel { red, green, blue, alpha }
    }

    pub const fn red() -> Self {
        Pixel {red: 255, blue: 0, green: 0, alpha: 255}
    }


    pub const fn green() -> Self {
        Pixel {red: 0, blue: 0, green: 255,  alpha: 255}
    }

    pub const fn blue() -> Self {
        Pixel {red: 0, blue: 255, green: 0,  alpha: 255}
    }

    pub const fn black() -> Self  {
        Pixel {red: 0, blue: 0, green: 0, alpha: 0}
    }

    pub const fn from_rgba32(rgba: u32) -> Self {
        let red = rgba & 0xFF;
        let blue = rgba >> 8 & 0xFF;
        let green = rgba >> 16 & 0xFF;
        let alpha = rgba >> 24 & 0xFF;
        Pixel {red,green,blue,alpha}
    }

    pub fn get_rgba32(&self) -> u32 {
        let red = self.red;
        let blue = self.blue;
        let green = self.green;
        let alpha = self.green;

        blue | (green << 8) | (red << 16) | (alpha << 24)
    }    

}