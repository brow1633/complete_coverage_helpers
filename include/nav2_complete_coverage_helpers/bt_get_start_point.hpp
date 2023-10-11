#ifndef NAV2_COMPLETE_COVERAGE_HELPERS__GET_START_POINT_
#define NAV2_COMPLETE_COVERAGE_HELPERS__GET_START_POINT_

#include <memory>
#include <string>
#include <chrono>

#include "behaviortree_cpp_v3/action_node.h"
#include "nav2_util/node_utils.hpp"
//#include "nav2_behavior_tree/bt_utils.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

namespace nav2_complete_coverage_helpers
{
    using namespace std::chrono_literals;

    class GetStartPoint : public BT::ActionNodeBase
    {
        public:
            GetStartPoint(
                    const std::string & xml_tag_name,
                    const BT::NodeConfiguration& conf)
                : BT::ActionNodeBase(xml_tag_name, conf) {}

            virtual ~GetStartPoint() {}

            void halt() override
            {
                setStatus(BT::NodeStatus::IDLE);
            }

            static BT::PortsList providedPorts() {
                return BT::PortsList (
                {
                    BT::InputPort<nav_msgs::msg::Path>("path", "Path to find start point of"),
                    BT::OutputPort<geometry_msgs::msg::PoseStamped>("start_point", "Start Point of path")
                });
            }

            virtual BT::NodeStatus on_success()
            {
                return BT::NodeStatus::SUCCESS;
            }

            virtual BT::NodeStatus on_aborted()
            {
                return BT::NodeStatus::FAILURE;
            }

            virtual BT::NodeStatus on_cancelled()
            {
                return BT::NodeStatus::SUCCESS;
            }

            BT::NodeStatus tick() override;

    };
}


#endif // NAV2_COMPLETE_COVERAGE_HELPERS__GET_START_POINT_
