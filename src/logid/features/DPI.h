/*
 * Copyright 2019-2020 PixlOne
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef LOGID_FEATURE_DPI_H
#define LOGID_FEATURE_DPI_H

#include <libconfig.h++>
#include "../backend/hidpp20/features/AdjustableDPI.h"
#include "DeviceFeature.h"
#include "../ipc/IPCInterface.h"

namespace logid {
namespace features
{
    class DPI : public DeviceFeature
    {
    public:
        explicit DPI(Device* dev);
        virtual void configure();
        virtual void listen();

        uint16_t getDPI(uint8_t sensor=0);
        void setDPI(uint16_t dpi, uint8_t sensor=0);
        uint8_t getSensorCount();
        backend::hidpp20::AdjustableDPI::SensorDPIList getSupportedDPIs(
                uint8_t sensor=0);

        class Config : public DeviceFeature::Config
        {
        public:
            explicit Config(Device* dev);
            uint16_t getDPI(uint8_t sensor) const;
            uint8_t getSensorCount() const;

            void setDPI(uint16_t dpi, uint8_t sensor);

            void save(libconfig::Setting& root) override;
        protected:
            std::vector<uint16_t> _dpis;
        };

        void saveConfig(libconfig::Setting& root) override;

        class IPC : public ipc::IPCInterface
        {
        public:
            IPC(DPI* dpi);
        private:
            DPI* _dpi;
        };
    private:
        Config _config;
        std::shared_ptr<backend::hidpp20::AdjustableDPI> _adjustable_dpi;
        std::vector<backend::hidpp20::AdjustableDPI::SensorDPIList> _dpi_lists;
        std::shared_ptr<IPC> _ipc_interface;
    };
 }}

#endif //LOGID_FEATURE_DPI_H
