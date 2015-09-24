#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);

    const double degree = M_PI/180;

    // message declarations
    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState joint_state;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "chassis";

    while (ros::ok()) {
        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(4); //Pioneer has 4 joint state definitions. 
        joint_state.position.resize(4);

        joint_state.name[0] = "p3at_back_right_wheel_joint";
        joint_state.position[0] = 0;

        joint_state.name[1] = "p3at_back_left_wheel_joint";
        joint_state.position[1] = 0;

        joint_state.name[2] = "p3at_front_left_wheel_joint";
        joint_state.position[2] = 0;

        joint_state.name[3] = "p3at_front_right_wheel_joint";
        joint_state.position[3] = 0; 

        //send the joint state and transform
        joint_pub.publish(joint_state);
        broadcaster.sendTransform(odom_trans);


        // This will adjust as needed per iteration
        loop_rate.sleep();
    }


    return 0;
}
