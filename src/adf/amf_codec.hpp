/*  Apex Engine Format Library
    Copyright(C) 2014-2020 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include "uni/model.hpp"

struct AmfStreamAttribute;

class AmfCodec : public uni::PrimitiveDescriptor {
public:
  const char *vertexBuffer;
  AmfStreamAttribute *attr;

  const char *RawBuffer() const override;
  size_t Offset() const override;
  size_t Stride() const override;
  size_t Index() const override;
  uni::FormatDescr Type() const override;
  uni::BBOX UnpackData() const override;
  UnpackDataType_e UnpackDataType() const override;
  Usage_e Usage() const override;
  uni::FormatCodec &Codec() const override;
};
