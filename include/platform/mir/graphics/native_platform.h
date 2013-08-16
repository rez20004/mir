/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Eleni Maria Stea <elenimaria.stea@canonical.com>
 */
#ifndef MIR_GRAPHICS_NATIVE_PLATFORM_H_
#define MIR_GRAPHICS_NATIVE_PLATFORM_H_

#include <memory>

namespace mir
{
namespace options
{
class Option;
}
namespace graphics
{
class NativePlatform
{
public:
    NativePlatform() {}

    virtual std::shared_ptr<GraphicBufferAllocator> create_buffer_allocator(
        std::shared_ptr<BufferInitializer> const& buffer_initializer) = 0;

    virtual ~NativePlatform() = default;
    NativePlatform(NativePlatform const&) = delete;
    NativePlatform& operator=(NativePlatform const&) = delete;
};

extern "C" typedef std::shared_ptr<NativePlatform>(*CreateNativePlatform)(/* TODO */);
extern "C" std::shared_ptr<NativePlatform> create_native_platform(/* TODO */);
}
}

#endif // MIR_GRAPHICS_NATIVE_PLATFORM_H_
