# ApexLib
ApexLib is independent serialize library for various formats used by Apex Engine.

In addition, it can extract class information from ADF files into readable XML format.

Library is compilable under VS 2015, 2017, 2019.

NOTE: RBM, RBN, RBS files are roughly converted into ADF format.

## Supported titles/formats
* The Hunter: RBM
* The Hunter - Primal: RBM
* The Hunter - Call of Wild: ADF (modelc, meshc)
* Just Cause 2: RBM
* Just Cause 3: RBM, ADF (vmodc [StuntAreas, DeformPoints])
* Just Cause 4: ADF (vmodc [StuntAreas, DeformPoints], modelc, meshc)
* Mad Max: RBN, RBS

Currently library supports only PC platform specific files.

## License
This library is available under GPL v3 license. (See LICENSE.md)

This library uses following libraries:

* PugiXml, Copyright (c) 2006-2019 Arseny Kapoulkine
* PreCore, Copyright (c) 2016-2019 Lukas Cone
