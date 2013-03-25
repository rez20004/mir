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
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_
#define MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_

#include <hardware/hwcomposer.h>
#include <gmock/gmock.h>

namespace mir
{
namespace test
{
namespace doubles
{

class ICSHardwareComposerInterface
{
public:
    virtual void registerProcs_interface(struct hwc_composer_device_1* dev, hwc_procs_t const* procs) = 0;
    virtual int eventControl_interface(struct hwc_composer_device_1* dev, int disp, int event, int enabled) = 0;
    virtual int set_interface(struct hwc_composer_device_1 *dev, size_t numDisplays, hwc_display_contents_1_t** displays) = 0;
};

class MockHWCComposerDevice1 : public hwc_composer_device_1, public ICSHardwareComposerInterface
{
public:
    MockHWCComposerDevice1()
    {
        common.version = HWC_DEVICE_API_VERSION_1_1;

        registerProcs = hook_registerProcs;
        eventControl = hook_eventControl;
        set = hook_set;
    }

    static void hook_registerProcs(struct hwc_composer_device_1* mock_hwc, hwc_procs_t const* procs)
    {
        MockHWCComposerDevice1* mocker = static_cast<MockHWCComposerDevice1*>(mock_hwc);
        return mocker->registerProcs_interface(mock_hwc, procs);
    }
    static int hook_eventControl(struct hwc_composer_device_1* mock_hwc, int disp, int event, int enabled)
    {
        MockHWCComposerDevice1* mocker = static_cast<MockHWCComposerDevice1*>(mock_hwc);
        return mocker->eventControl_interface(mock_hwc, disp, event, enabled);
    }
    static int hook_set(struct hwc_composer_device_1 *mock_hwc, size_t numDisplays, hwc_display_contents_1_t** displays)
    {
        MockHWCComposerDevice1* mocker = static_cast<MockHWCComposerDevice1*>(mock_hwc);
        return mocker->set_interface(mock_hwc, numDisplays, displays);
    }

    MOCK_METHOD2(registerProcs_interface, void(struct hwc_composer_device_1*, hwc_procs_t const*));
    MOCK_METHOD4(eventControl_interface, int(struct hwc_composer_device_1* dev, int disp, int event, int enabled));
    MOCK_METHOD3(set_interface, int(struct hwc_composer_device_1 *, size_t, hwc_display_contents_1_t**));
};

}
}
}

#endif /* MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_ */
