/*
 * Copyright © 2017 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 2 or 3,
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
 * Authored by:
 *   Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#ifndef MIR_PLATFORM_GRAPHICS_WAYLAND_ALLOCATOR_H_
#define MIR_PLATFORM_GRAPHICS_WAYLAND_ALLOCATOR_H_

#include <vector>
#include <memory>

#include <wayland-server-core.h>

namespace mir
{
namespace graphics
{
class Buffer;

class WaylandAllocator
{
public:
    virtual ~WaylandAllocator() = default;

    virtual void bind_display(wl_display* display) = 0;
    virtual std::shared_ptr<Buffer> buffer_from_resource(
        wl_resource* buffer,
        std::function<void()>&& on_consumed,
        std::function<void()>&& on_release) = 0;
};
}
}

#endif //MIR_PLATFORM_GRAPHICS_WAYLAND_ALLOCATOR_H_
