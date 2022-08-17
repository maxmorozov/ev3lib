//
// ReversedEncoderMotor.h
//

#pragma once

#include <utils/type_utils.h>
#include <robotics/EncoderMotor.h>

namespace ev3lib::robotics {

    /**
     * Wrapper for an unregulated motor that makes it to work as a reversed motor.
     */
    class ReversedEncoderMotor : public EncoderMotor {
    private:
        std::unique_ptr<EncoderMotor> encoderMotor;

    public:
        /**
         * Uses moving constructor to transfer the parameter to the   
         *
         * @tparam T
         * @param motor
         */
        template<utils::DerivedMovable<EncoderMotor> T>
        explicit ReversedEncoderMotor(T motor)
                : encoderMotor(std::make_unique<T>(std::move(motor))) {
        }

        unsigned int getPower() const override {
            return encoderMotor->getPower();
        }

        void setPower(uint power) override {
            encoderMotor->setPower(power);
        }

        void backward() override {
            encoderMotor->forward();
        }

        void flt() override {
            encoderMotor->flt();
        }

        void forward() override {
            encoderMotor->backward();
        }

        bool isMoving() override {
            return encoderMotor->isMoving();
        }

        void stop() override {
            encoderMotor->stop();
        }

        int getTachoCount() const override {
            return -encoderMotor->getTachoCount();
        }

        void resetTachoCount() override {
            encoderMotor->resetTachoCount();
        }
    };

} // robotics
