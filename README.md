# ApexLib
[![Build Status](https://travis-ci.org/PredatorCZ/ApexLib.svg?branch=master)](https://travis-ci.org/PredatorCZ/ApexLib)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/52cdffd9e9c84e4698f1c525d5d449fd)](https://www.codacy.com/app/PredatorCZ/ApexLib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PredatorCZ/ApexLib&amp;utm_campaign=Badge_Grade)

ApexLib is independent serialize library for various formats used by Apex Engine.

In addition, it can extract class information from ADF files into readable XML format.

Library is compilable under VS 2015 and later, and GCC 6 and later

NOTE: RBM, RBN, RBS files are roughly converted into ADF format.

## Supported titles/formats
  * The Hunter: RBM
  * The Hunter - Primal: RBM
  * The Hunter - Call of Wild: ADF (modelc, meshc)
  * Just Cause 2: RBM
  * Just Cause 3: RBM, ADF (vmodc \[StuntAreas, DeformPoints\])
  * Just Cause 4: ADF (vmodc \[StuntAreas, DeformPoints\], modelc, meshc)
  * Mad Max: RBN, RBS
  * Generation Zero: ADF (modelc, meshc)
  * RAGE 2 ADF (modelc, meshc)
  * All: AVTX (ddsc)

Currently library supports only PC platform specific files.

## License
This library is available under GPL v3 license. (See LICENSE.md)

This library uses following libraries:

  * PugiXml, Copyright (c) 2006-2019 Arseny Kapoulkine
  * PreCore, Copyright (c) 2016-2019 Lukas Cone
  * ZStandard, Copyright (c) 2016-present, Facebook, Inc. All rights reserved.
