//* vim: ft=cpp

//* NTSC to RGB color conversion. This is influenced by the color tint bits.
//* Palette borrowed from Beannaich.
//* TODO: Generate automatically.

uint32_t const nes_to_rgb[8][64] =
    //* No emphasis
  { { 0x656565, 0x032863, 0x1a1978, 0x320c75, 0x47065d, 0x520835, 0x511109, 0x431f00,
        0x2d2e00, 0x143a00, 0x004000, 0x003f11, 0x00363e, 0x000000, 0x000000, 0x000000,
      0xaeaeae, 0x2c5cac, 0x4a48c7, 0x6b38c4, 0x8630a3, 0x95336f, 0x933f33, 0x815102,
        0x646500, 0x437500, 0x277d0a, 0x187b3f, 0x1a6f7a, 0x000000, 0x000000, 0x000000,
      0xffffff, 0x7bacfc, 0x9998ff, 0xba87ff, 0xd67ff4, 0xe582be, 0xe38e82, 0xd1a050,
        0xb3b535, 0x92c538, 0x76cd59, 0x67cb8e, 0x69bfca, 0x4e4e4e, 0x000000, 0x000000,
      0xffffff, 0xc8dcfe, 0xd5d4ff, 0xe2cdff, 0xeecafa, 0xf4cbe4, 0xf3d0cb, 0xecd8b7,
        0xdfe0ab, 0xd2e7ad, 0xc6eaba, 0xc0e9d0, 0xc1e4e9, 0xb6b6b6, 0x000000, 0x000000 },

    //* Emphasize red
    { 0x5e4643, 0x000d3f, 0x130253, 0x2c0054, 0x400042, 0x4d0022, 0x4f0700, 0x401100,
        0x2a1b00, 0x112300, 0x002500, 0x002100, 0x00161b, 0x000000, 0x000000, 0x000000,
      0xa4837e, 0x23377a, 0x412995, 0x611f96, 0x7d1c7d, 0x8e2253, 0x903023, 0x7c3c00,
        0x5f4a00, 0x3e5400, 0x225800, 0x12521b, 0x10444b, 0x000000, 0x000000, 0x000000,
      0xf1c6c1, 0x6f7abc, 0x8d6cd7, 0xae61d8, 0xca5ec0, 0xdb6495, 0xdd7264, 0xc97f34,
        0xab8d19, 0x8a9718, 0x6e9b31, 0x5d955b, 0x5b868c, 0x47322f, 0x000000, 0x000000,
      0xf1c6c1, 0xbba7bf, 0xc8a1ca, 0xd59dca, 0xe19bc0, 0xe89eaf, 0xe9a49b, 0xe0a987,
        0xd4af7c, 0xc7b37b, 0xbbb485, 0xb4b297, 0xb3acab, 0xab8985, 0x000000, 0x000000 },

    //* Emphasize green
    { 0x3f5737, 0x001e3d, 0x000e4c, 0x120147, 0x21002f, 0x2e000f, 0x2f0800, 0x261700,
        0x162700, 0x033400, 0x003c00, 0x003800, 0x002d1f, 0x000000, 0x000000, 0x000000,
      0x7a9b6e, 0x0f4f76, 0x253a8a, 0x3e2884, 0x521d64, 0x632339, 0x65310a, 0x594500,
        0x425a00, 0x296c00, 0x157700, 0x05711f, 0x03634f, 0x000000, 0x000000, 0x000000,
      0xbae6ac, 0x4e99b4, 0x6483c8, 0x7e71c1, 0x9267a1, 0xa36c76, 0xa57b46, 0x998f1d,
        0x83a409, 0x69b610, 0x55c130, 0x44bb5b, 0x42ad8b, 0x2c4225, 0x000000, 0x000000,
      0xbae6ac, 0x8ec6af, 0x97bdb7, 0xa1b6b5, 0xaab1a7, 0xb1b496, 0xb2ba82, 0xadc271,
        0xa3cb69, 0x99d26c, 0x90d779, 0x8ad48a, 0x89ce9e, 0x80a274, 0x000000, 0x000000 },

    //* Emphasize red+green
    { 0x3e3e2c, 0x000930, 0x00003f, 0x11003e, 0x21002c, 0x2d000c, 0x2f0000, 0x250a00,
        0x141500, 0x021e00, 0x002300, 0x001e00, 0x001414, 0x000000, 0x000000, 0x000000,
      0x787860, 0x0e3265, 0x242379, 0x3d1777, 0x52115f, 0x621734, 0x642505, 0x573300,
        0x414200, 0x284e00, 0x145400, 0x034e10, 0x014040, 0x000000, 0x000000, 0x000000,
      0xb8b999, 0x4d729e, 0x6463b2, 0x7c56b0, 0x915098, 0xa2566d, 0xa4653c, 0x967317,
        0x808202, 0x678e05, 0x52941d, 0x428e48, 0x408079, 0x2b2c1c, 0x000000, 0x000000,
      0xb8b999, 0x8c9b9b, 0x9595a3, 0xa090a2, 0xa88e98, 0xaf9087, 0xb09673, 0xaa9c63,
        0xa1a25b, 0x97a75c, 0x8eaa66, 0x87a778, 0x87a18c, 0x7e7f65, 0x000000, 0x000000 },

    //* Emphasize blue
    { 0x49496c, 0x001a65, 0x110f7a, 0x240275, 0x33005d, 0x3a0038, 0x36000e, 0x270700,
        0x111200, 0x001f00, 0x002700, 0x002818, 0x002342, 0x000000, 0x000003, 0x000003,
      0x8787b7, 0x1f49af, 0x3d3bca, 0x5629c4, 0x6a1ea4, 0x731d72, 0x6e233b, 0x5a300c,
        0x3d3e00, 0x244f00, 0x0f5a17, 0x065c48, 0x0c5580, 0x000003, 0x000003, 0x000003,
      0xcccbff, 0x638cff, 0x807eff, 0x9a6cff, 0xae62f7, 0xb860c5, 0xb2678c, 0x9e735d,
        0x818141, 0x679348, 0x539e68, 0x49a09a, 0x4f99d2, 0x353554, 0x000003, 0x000003,
      0xcccbff, 0xa1b1ff, 0xadacff, 0xb7a4ff, 0xc0a0ff, 0xc49fee, 0xc1a2d7, 0xb9a7c3,
        0xadadb8, 0xa2b4bb, 0x9ab9c8, 0x96b9dd, 0x98b7f4, 0x8e8dc0, 0x000003, 0x000003 },

    //* Emphasize blue+red
    { 0x433747, 0x000840, 0x0b0055, 0x1d0053, 0x2d0041, 0x350023, 0x340002, 0x250200,
        0x0f0c00, 0x001500, 0x001900, 0x001800, 0x00111d, 0x000000, 0x000000, 0x000000,
      0x7f6e84, 0x17307c, 0x342297, 0x4d1695, 0x61107d, 0x6c1255, 0x6b1b29, 0x572800,
        0x3a3500, 0x214100, 0x0d4700, 0x024620, 0x033d4d, 0x000000, 0x000000, 0x000000,
      0xc1abc8, 0x586dc0, 0x765fdb, 0x8e52d9, 0xa34cc0, 0xae4e99, 0xad576c, 0x99643c,
        0x7b7221, 0x627e23, 0x4e843b, 0x428263, 0x447990, 0x302533, 0x000000, 0x000000,
      0xc1abc8, 0x9692c5, 0xa28cd0, 0xac87cf, 0xb584c5, 0xb985b5, 0xb989a2, 0xb18e8f,
        0xa49483, 0x9a9984, 0x929b8e, 0x8d9a9f, 0x8e97b1, 0x85748b, 0x000000, 0x000000 },

    //* Emphasize blue+green
    { 0x344041, 0x001240, 0x00064f, 0x0e004a, 0x1e0032, 0x260015, 0x250000, 0x1b0300,
        0x0a0f00, 0x001c00, 0x002400, 0x002303, 0x001c24, 0x000000, 0x000000, 0x000000,
      0x6a7a7c, 0x093d7b, 0x1f2f8f, 0x381d88, 0x4d1269, 0x581441, 0x561d15, 0x492b00,
        0x333900, 0x1a4b00, 0x055602, 0x00542a, 0x004b56, 0x000000, 0x000000, 0x000000,
      0xa6bbbe, 0x447ebc, 0x5a6ed1, 0x745cca, 0x8852aa, 0x935382, 0x925c55, 0x846a30,
        0x6e7a1c, 0x558c22, 0x409642, 0x35956a, 0x368c97, 0x222d2e, 0x000000, 0x000000,
      0xa6bbbe, 0x7ea2bd, 0x879cc6, 0x9194c3, 0x9a90b6, 0x9e90a5, 0x9e9493, 0x989a83,
        0x8fa07b, 0x84a87e, 0x7cac8b, 0x77ab9b, 0x78a8ae, 0x708183, 0x000000, 0x000000 },

    //* Emphasize all
    { 0x343434, 0x000633, 0x000042, 0x0e0040, 0x1e002e, 0x260010, 0x250000, 0x1b0000,
        0x0a0b00, 0x001400, 0x001900, 0x001700, 0x001117, 0x000000, 0x000000, 0x000000,
      0x6a6a6a, 0x0a2d69, 0x201f7d, 0x38137a, 0x4d0d62, 0x580e3b, 0x56170f, 0x492500,
        0x333400, 0x1a4000, 0x064600, 0x004417, 0x003b44, 0x000000, 0x000000, 0x000000,
      0xa6a6a6, 0x4569a5, 0x5b5ab9, 0x744db7, 0x88479e, 0x944977, 0x92524a, 0x846024,
        0x6e6f10, 0x557c12, 0x41822b, 0x358052, 0x37777f, 0x232323, 0x000000, 0x000000,
      0xa6a6a6, 0x7e8da6, 0x8787ae, 0x9282ad, 0x9a7fa3, 0x9f8093, 0x9e8480, 0x988a71,
        0x8f9068, 0x859569, 0x7c9773, 0x789784, 0x789396, 0x707070, 0x000000, 0x000000 } };