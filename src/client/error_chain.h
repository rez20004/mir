/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_CLIENT_ERROR_CHAIN_H
#define MIR_CLIENT_ERROR_CHAIN_H

#include "mir_presentation_chain.h"
#include "mir/geometry/size.h"
#include "mir_toolkit/mir_presentation_chain.h"
#include "mir_protobuf.pb.h"
#include "buffer.h"
#include <mutex>
#include <memory>

namespace mir
{
namespace client
{

class ErrorChain : public MirPresentationChain
{
public:
    ErrorChain(
        MirConnection* connection,
        std::shared_ptr<MirWaitHandle> const&,
        int id,
        std::string const& error_msg);
    void allocate_buffer(
        geometry::Size size, MirPixelFormat format, MirBufferUsage usage, mir_buffer_callback, void*);
    void submit_buffer(MirBuffer* buffer);
    void release_buffer(MirBuffer* buffer);
    void buffer_available(mir::protobuf::Buffer const& buffer) override;
    void buffer_unavailable() override;
    MirConnection* connection() const;
    int rpc_id() const override;
    std::string error_msg() const override;
private:
    MirConnection* const connection_;
    std::shared_ptr<MirWaitHandle> const wait_handle;
    int const stream_id;
    std::string const error;
};

}
}
#endif /* MIR_CLIENT_ERROR_CHAIN_H */
