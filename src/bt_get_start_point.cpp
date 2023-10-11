#include <memory>
#include <string>

#include "nav2_complete_coverage_helpers/bt_get_start_point.hpp"

namespace nav2_complete_coverage_helpers
{
    BT::NodeStatus GetStartPoint::tick()
    {
        nav_msgs::msg::Path path_;

        if (!getInput("path", path_))
        {
            return BT::NodeStatus::FAILURE;
        }

        if (path_.poses.empty())
        {
            return BT::NodeStatus::FAILURE;
        }

        geometry_msgs::msg::PoseStamped pose_;

        pose_ = path_.poses[0];
        setOutput("start_point", pose_);

        return BT::NodeStatus::SUCCESS;
    }
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    BT::NodeBuilder builder =
        [](const std::string & name, const BT::NodeConfiguration & config)
        {
            return std::make_unique<nav2_complete_coverage_helpers::GetStartPoint>(
                    name, config);
        };

    factory.registerBuilder<nav2_complete_coverage_helpers::GetStartPoint>(
            "GetStartPoint", builder);
}
