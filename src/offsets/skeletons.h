#pragma once
#include <cstdint>

namespace Skeletons {
    namespace CT {
        enum BONES {
            // top
            head = 6,
            neck = 5,
            torso1 = 4,
            // left arm
            left_shoulder = 61,
            left_elbow = 9,
            left_hand = 53,
            // right arm
            right_shoulder = 86,
            right_elbow = 14,
            right_hand = 63,
            // bottom
            torso2 = 2,
            pelvis = 1,
            // left leg
            upper_left_leg = 22,
            left_knee = 23,
            left_foot = 24,
            // right leg
            upper_right_leg = 25,
            right_knee = 26,
            right_foot = 27
        };

        constexpr int ct_array[] = {
            CT::head, CT::neck, CT::torso1,
            // down left arm
            CT::left_shoulder, CT::left_elbow, CT::left_hand,
            // back up left arm
            CT::left_elbow, CT::left_shoulder,
            // back to torso
            CT::torso1,
            // down right arm
            CT::right_shoulder, CT::right_elbow, CT::right_hand,
            // back up right arm
            CT::right_elbow, CT::right_shoulder,
            // back to torso
            CT::torso1,
            // down body
            CT::torso2, CT::pelvis,
            // down left leg
            CT::upper_left_leg, CT::left_knee, CT::left_foot,
            // up left leg
            CT::left_knee, CT::upper_left_leg,
            // back to pelvis
            CT::pelvis,
            // down right leg
            CT::upper_right_leg, CT::right_knee, CT::right_foot,
        };
    }

    namespace T {
        enum BONES {
            // top
            head = 6,
            neck = 5,
            torso1 = 4,
            // left arm
            left_shoulder = 61,
            left_elbow = 9,
            left_hand = 53,
            // right arm
            right_shoulder = 86,
            right_elbow = 14,
            right_hand = 63,
            // bottom
            torso2 = 2,
            pelvis = 1,
            // left leg
            upper_left_leg = 22,
            left_knee = 23,
            left_foot = 24,
            // right leg
            upper_right_leg = 25,
            right_knee = 26,
            right_foot = 27
        };
        constexpr int t_array[] = {
            T::head, T::neck, T::torso1,
            // down left arm
            T::left_shoulder, T::left_elbow, T::left_hand,
            // back up left arm
            T::left_elbow, T::left_shoulder,
            // back to torso
            T::torso1,
            // down right arm
            T::right_shoulder, T::right_elbow, T::right_hand,
            // back up right arm
            T::right_elbow, T::right_shoulder,
            // back to torso
            T::torso1,
            // down body
            T::torso2, T::pelvis,
            // down left leg
            T::upper_left_leg, T::left_knee, T::left_foot,
            // up left leg
            T::left_knee, T::upper_left_leg,
            // back to pelvis
            T::pelvis,
            // down right leg
            T::upper_right_leg, T::right_knee, T::right_foot,
        };
    }
}
