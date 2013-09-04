/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_STUB_BUFFER_H_
#define MIR_TEST_DOUBLES_STUB_BUFFER_H_

#include "mir/graphics/buffer_basic.h"
#include "mir/graphics/buffer_properties.h"
#include "mir/geometry/size.h"
#include "mir/graphics/buffer_id.h"

namespace mir
{
namespace test
{
namespace doubles
{

class StubBuffer : public graphics::BufferBasic
{
public:
    StubBuffer()
        : buf_size{0, 0},
          buf_pixel_format{geometry::PixelFormat::abgr_8888}
    {
    }

    StubBuffer(graphics::BufferProperties const& properties)
        : buf_size{properties.size},
          buf_pixel_format{properties.format}
    {
    }

    virtual geometry::Size size() const { return buf_size; }

    virtual geometry::Stride stride() const { return geometry::Stride(); }

    virtual geometry::PixelFormat pixel_format() const { return buf_pixel_format; }

    virtual std::shared_ptr<MirNativeBuffer> native_buffer_handle() const
    {
#ifndef ANDROID
        return std::make_shared<MirNativeBuffer>();
#else
        return std::shared_ptr<MirNativeBuffer>();
#endif
    }
    virtual void bind_to_texture() {}

    virtual bool can_bypass() const override { return false; }

    geometry::Size const buf_size;
    geometry::PixelFormat const buf_pixel_format;
};
}
}
}
#endif /* MIR_TEST_DOUBLES_STUB_BUFFER_H_ */
