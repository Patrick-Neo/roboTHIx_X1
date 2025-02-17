#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <string>
#include <iostream>
#include <std_msgs/String.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>

std::string s;

void callback(const std_msgs::String &msg)
{
  s = msg.data;
}

void callback_radiation(const std_msgs::Bool &msg)
{

  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "marker_transfom");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  tf::TransformListener marker_listener;
  tf::StampedTransform transform;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "base_footprint";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "Geiger_Zaheler";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header

    // try
    // {
    //   marker_listener.lookupTransform("base_footprint", "world", ros::Time(0), transform);
    // }
    // catch (tf::TransformException &ex)
    // {
    //   ROS_ERROR("%s", ex.what());
    // }

    // marker.pose.position.x = transform.getOrigin().x();
    // marker.pose.position.y = transform.getOrigin().y();
    // marker.pose.position.z = transform.getOrigin().z();

    marker.pose.position.x = 1.0;
    marker.pose.position.y = 1.0;
    marker.pose.position.z = 1.0;

    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    ros::Subscriber sub_0 = n.subscribe("geigerTicksPerS", 10, &callback);

    marker.text = s;

    marker.lifetime = ros::Duration();
    // ros::Subscriber sub_1 = n.subscribe("Radiation_Button",10);

    // Publish the marker
    // while (marker_pub.getNumSubscribers() < 1)
    // {
    //   if (!ros::ok())
    //   {
    //     return 0;
    //   }
    //   ROS_WARN_ONCE("Please create a subscriber to the marker");
    //   sleep(1);
    // }
    marker_pub.publish(marker);
    ros::spinOnce();

    r.sleep();
  }
}