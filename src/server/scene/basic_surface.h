/*
 * Copyright © 2012-2014 Canonical Ltd.
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
 * Authored by: Thomas Voss <thomas.voss@canonical.com>
 */

#ifndef MIR_SCENE_BASIC_SURFACE_H_
#define MIR_SCENE_BASIC_SURFACE_H_

#include "mir/frontend/surface_id.h"
#include "mir/geometry/rectangle.h"
#include "mir/graphics/renderable.h"
#include "mir/input/surface.h"
#include "mir/shell/surface.h"

#include "mutable_surface_state.h"
#include "mir_toolkit/common.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <mutex>
#include <string>

namespace mir
{
namespace compositor
{
struct BufferIPCPackage;
class BufferStream;
}
namespace frontend { class EventSink; }
namespace graphics
{
class Buffer;
}
namespace input
{
class InputChannel;
class Surface;
}
namespace shell { class SurfaceConfigurator; }
namespace scene
{
class SceneReport;

class BasicSurface :
    public graphics::Renderable,
    public input::Surface,
    public MutableSurfaceState,
    public shell::Surface
{
public:
    BasicSurface(
        frontend::SurfaceId id,
        std::string const& name,
        geometry::Rectangle rect,
        std::function<void()> change_cb,
        bool nonrectangular,
        std::shared_ptr<compositor::BufferStream> const& buffer_stream,
        std::shared_ptr<input::InputChannel> const& input_channel,
        std::shared_ptr<frontend::EventSink> const& event_sink,
        std::shared_ptr<shell::SurfaceConfigurator> const& configurator,
        std::shared_ptr<SceneReport> const& report);

    ~BasicSurface() noexcept;

    std::string name() const override;
    void move_to(geometry::Point const& top_left) override;
    float alpha() const override;
    void set_hidden(bool is_hidden) override;

    geometry::Size size() const override;

    MirPixelFormat pixel_format() const;

    std::shared_ptr<graphics::Buffer> snapshot_buffer() const;
    void swap_buffers(graphics::Buffer* old_buffer, std::function<void(graphics::Buffer* new_buffer)> complete);
    void force_requests_to_complete();

    bool supports_input() const;
    int client_input_fd() const;
    void allow_framedropping(bool);
    std::shared_ptr<input::InputChannel> input_channel() const;

    void set_input_region(std::vector<geometry::Rectangle> const& input_rectangles) override;

    std::shared_ptr<compositor::BufferStream> buffer_stream() const;

    void resize(geometry::Size const& size) override;
    geometry::Point top_left() const override;
    bool contains(geometry::Point const& point) const override;
    void frame_posted();
    void set_alpha(float alpha) override;
    void set_transformation(glm::mat4 const&) override;
    glm::mat4 transformation() const override;
    bool should_be_rendered_in(geometry::Rectangle const& rect) const  override;
    bool shaped() const  override;  // meaning the pixel format has alpha

    // Renderable interface
    std::shared_ptr<graphics::Buffer> buffer(unsigned long) const override;
    bool alpha_enabled() const override;
    geometry::Rectangle screen_position() const override;
    int buffers_ready_for_compositor() const override;

    void with_most_recent_buffer_do(
        std::function<void(graphics::Buffer&)> const& exec) override;

    MirSurfaceType type() const override;
    MirSurfaceState state() const override;
    void take_input_focus(std::shared_ptr<shell::InputTargeter> const& targeter) override;
    void raise(std::shared_ptr<SurfaceRanker> const& controller) override;
    int configure(MirSurfaceAttrib attrib, int value) override;
    void hide() override;
    void show() override;

private:
    bool set_type(MirSurfaceType t);  // Use configure() to make public changes
    bool set_state(MirSurfaceState s);
    void notify_attrib_change(MirSurfaceAttrib attrib, int value);

    std::mutex mutable guard;
    frontend::SurfaceId const id;
    std::function<void()> const notify_change;
    std::string const surface_name;
    geometry::Rectangle surface_rect;
    glm::mat4 transformation_matrix;
    float surface_alpha;
    bool first_frame_posted;
    bool hidden;
    const bool nonrectangular;
    std::vector<geometry::Rectangle> input_rectangles;
    std::shared_ptr<compositor::BufferStream> const surface_buffer_stream;
    std::shared_ptr<input::InputChannel> const server_input_channel;
    std::shared_ptr<frontend::EventSink> const event_sink;
    std::shared_ptr<shell::SurfaceConfigurator> const configurator;
    std::shared_ptr<SceneReport> const report;

    MirSurfaceType type_value;
    MirSurfaceState state_value;
};

}
}

#endif // MIR_SCENE_BASIC_SURFACE_H_
