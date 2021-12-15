
void updateRosbotOdometry(RosbotDrive *drive, RosbotOdometry_t *odom, float dtime)
{
    double curr_wheel_R_ang_pos;
    double curr_wheel_L_ang_pos;
    odom->wheel_FR_ang_pos = drive->getAngularPos(MOTOR_FR);
    odom->wheel_FL_ang_pos = drive->getAngularPos(MOTOR_FL);
    odom->wheel_RR_ang_pos = drive->getAngularPos(MOTOR_RR);
    odom->wheel_RL_ang_pos = drive->getAngularPos(MOTOR_RL);
    if (drive->getRosbotDriveType() == 4)
    {
        curr_wheel_R_ang_pos = (odom->wheel_FR_ang_pos + odom->wheel_RR_ang_pos) / (2 * TYRE_DEFLATION);
        curr_wheel_L_ang_pos = (odom->wheel_FL_ang_pos + odom->wheel_RL_ang_pos) / (2 * TYRE_DEFLATION);
    }
    else
    {
        curr_wheel_R_ang_pos = odom->wheel_FR_ang_pos;
        curr_wheel_L_ang_pos = odom->wheel_FL_ang_pos;
    }
    odom->wheel_L_ang_vel = (curr_wheel_L_ang_pos - odom->wheel_L_ang_pos) / (dtime);
    odom->wheel_R_ang_vel = (curr_wheel_R_ang_pos - odom->wheel_R_ang_pos) / (dtime);
    odom->wheel_L_ang_pos = curr_wheel_L_ang_pos;
    odom->wheel_R_ang_pos = curr_wheel_R_ang_pos;
    odom->robot_angular_vel = (((odom->wheel_R_ang_pos - odom->wheel_L_ang_pos) * WHEEL_RADIUS / (ROBOT_WIDTH * DIAMETER_MODIFICATOR)) - odom->robot_angular_pos) / dtime;
    odom->robot_angular_pos = (odom->wheel_R_ang_pos - odom->wheel_L_ang_pos) * WHEEL_RADIUS / (ROBOT_WIDTH * DIAMETER_MODIFICATOR);
    odom->robot_x_vel = (odom->wheel_L_ang_vel * WHEEL_RADIUS + odom->robot_angular_vel * ROBOT_WIDTH_HALF) * cos(odom->robot_angular_pos);
    odom->robot_y_vel = (odom->wheel_L_ang_vel * WHEEL_RADIUS + odom->robot_angular_vel * ROBOT_WIDTH_HALF) * sin(odom->robot_angular_pos);
    odom->robot_x_pos = odom->robot_x_pos + odom->robot_x_vel * dtime;
    odom->robot_y_pos = odom->robot_y_pos + odom->robot_y_vel * dtime;
}