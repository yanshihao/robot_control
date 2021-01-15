#pragma once
#include "../include/robot_control/ultils.h"
#include <cmath>
#include <std_msgs/Float64.h>
#include <vector>
using namespace std;
class EightTrajectory
: public Trajectory
{
public:
    virtual Location getLocation( double time ) override
    {
        double xr = 1.1 + 0.7 * sin(2 * PI * time / DIVISOR);
        double yr = 0.9 + 0.7 * sin(4 * PI * time / DIVISOR);
        double xr_dot = 0.7 * cos(2 * PI * time / DIVISOR) * 2.0 * PI / DIVISOR;
        double yr_dot = 0.7 * cos(4 * PI * time / DIVISOR) * 4.0 * PI / DIVISOR;
        double thetar = atan2(yr_dot, xr_dot);
        return Location( xr, yr, thetar );
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        double xr = 1.1 + 0.7 * sin(2 * PI * time / DIVISOR);
        double yr = 0.9 + 0.7 * sin(4 * PI * time / DIVISOR);
        double xr_dot = 0.7 * cos(2 * PI * time / DIVISOR) * 2.0 * PI / DIVISOR;
        double yr_dot = 0.7 * cos(4 * PI * time / DIVISOR) * 4.0 * PI / DIVISOR;
        double thetar = atan2(yr_dot, xr_dot);
        double xr_dot_dot = -0.7 * sin(2 * PI * time / DIVISOR) * 2 * PI / DIVISOR * 2 * PI / DIVISOR;
        double yr_dot_dot = -0.7 * sin(4 * PI * time / DIVISOR) * 4 * PI / DIVISOR * 4 * PI / DIVISOR;
        double vr = sqrt(xr_dot * xr_dot + yr_dot * yr_dot);    
        double wr = (xr_dot * yr_dot_dot - yr_dot * xr_dot_dot) / (xr_dot * xr_dot + yr_dot * yr_dot);
        return PathInfo( xr,yr,thetar, wr, vr );
    }
};

// 圆形轨迹，需要设置圆心和半径
class CircleTrajectory
:public Trajectory
{
public:
    CircleTrajectory(double x = 0, double y = 0, double theta = 0,
                    double r = 1.5, double speed = 0.2)
    : x_(x), y_(y), theta_(theta) , r_(r), speed_(speed)
    {
        centerX_ = x_ - r_ * sin(theta_);
        centerY_ = y_ + r_ * cos(theta_);
        w_ = speed_ / r_;
        v_ = speed_;
    }
    virtual Location getLocation( double time ) override
    {
        double xr = centerX_ + r_ * cos( w_ * time + theta_ - PI/2 );
        double yr = centerY_ + r_ * sin( w_ * time + theta_ - PI/2 );
        double xr_dot = - v_ * sin( w_ * time + theta_ - PI/2 );
        double yr_dot = v_ * cos( w_ * time + theta_ - PI/2 );
        double thetar = getAngle(w_ * time + theta_);
        return Location( xr, yr, thetar );
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        double xr = centerX_ + r_ * cos( w_ * time + theta_ - PI/2 );
        double yr = centerY_ + r_ * sin( w_ * time + theta_ - PI/2 );
        double xr_dot = - v_ * sin( w_ * time + theta_ - PI/2 );
        double yr_dot = v_ * cos( w_ * time + theta_ - PI/2 );
        double thetar = getAngle(w_ * time + theta_);
        double xr_dot_dot = - v_ * w_ * cos( w_ * time + theta_ - PI/2 );
        double yr_dot_dot = - v_ * w_ * sin( w_ * time + theta_ - PI/2 );
        double vr = speed_;    
        double wr = w_;
        return PathInfo( xr,yr,thetar, wr, vr );
    }
private:
    // 根据原点位置和速度来进行
    double x_;
    double y_;
    double theta_;
    double r_;
    double speed_;
    double v_;
    double w_;
    double centerX_;
    double centerY_;
};

// 线条装轨迹，可以设置多个方向
class LineTrajectory
: public Trajectory
{
public:
    LineTrajectory(double x = 0, double y = 0, double theta = 0, double speed = 0.2)
    : x_(x), y_(y), theta_(theta), speed_(speed)
    {}
    virtual Location getLocation( double time ) override
    {
        double xr = x_ + speed_ * cos( theta_ ) * time;
        double yr = y_ + speed_ * sin( theta_ ) * time;
        double xr_dot = speed_ * cos( theta_ );
        double yr_dot = speed_ * sin( theta_ );
        double thetar = theta_;
        return Location( xr, yr, thetar );
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        double xr = x_ + speed_ * cos( theta_ ) * time;
        double yr = y_ + speed_ * sin( theta_ ) * time;
        double xr_dot = speed_ * cos( theta_ );
        double yr_dot = speed_ * sin( theta_ );
        double thetar = theta_;
        double xr_dot_dot = 0;
        double yr_dot_dot = 0;
        double vr = speed_;    
        double wr = 0;
        return PathInfo( xr,yr,thetar, wr, vr );
    }
private:
    // 根据原点位置和速度来进行
    double x_;
    double y_;
    double theta_;
    double speed_;
};

// J型轨迹
class JTypeTrajectory
: public Trajectory
{
    // 先直线然后在圆形
public:
    JTypeTrajectory(double x = 0, double y = 0, double theta = 0, double length = 1,
                    double speed = 0.2, double r = 1)
    : x_(x), y_(x), theta_(theta), length_(length), speed_(speed), r_(r)
    {
        centerX_ = x_ + length_ * cos(theta_) - r_ * sin(theta_);
        centerY_ = y_ + length_ * sin(theta_) + r_ * cos(theta_);
        t1_ = length_ / speed_;
        w_ = speed_ / r_;
        v_ = speed_;
    }

    virtual Location getLocation( double time ) override
    {
        if( time < t1_ )
        {
            double xr = x_ + speed_ * cos( theta_ ) * time;
            double yr = y_ + speed_ * sin( theta_ ) * time;
            double xr_dot = speed_ * cos( theta_ );
            double yr_dot = speed_ * sin( theta_ );
            double thetar = theta_;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( w_ * time1 + theta_ - PI/2 );
            double yr = centerY_ + r_ * sin( w_ * time1 + theta_ - PI/2 );
            double xr_dot = - v_ * sin( w_ * time1 + theta_ - PI/2 );
            double yr_dot = v_ * cos( w_ * time1 + theta_ - PI/2 );
            double thetar = getAngle(w_ * time1 + theta_);
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        if( time < t1_ )
        {
            double xr = x_ + speed_ * cos( theta_ ) * time;
            double yr = y_ + speed_ * sin( theta_ ) * time;
            double xr_dot = speed_ * cos( theta_ );
            double yr_dot = speed_ * sin( theta_ );
            double thetar = theta_;
            double xr_dot_dot = 0;
            double yr_dot_dot = 0;
            double vr = speed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( w_ * time1 + theta_ - PI/2 );
            double yr = centerY_ + r_ * sin( w_ * time1 + theta_ - PI/2 );
            double xr_dot = - v_ * sin( w_ * time1 + theta_ - PI/2 );
            double yr_dot = v_ * cos( w_ * time1 + theta_ - PI/2 );
            double thetar = getAngle(w_ * time1 + theta_);
            double xr_dot_dot = - v_ * w_ * cos( w_ * time1 + theta_ - PI/2 );
            double yr_dot_dot = - v_ * w_ * sin( w_ * time1 + theta_ - PI/2 );
            double vr = speed_;    
            double wr = w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }
private:
    double x_;
    double y_;
    double theta_;
    double length_;
    double speed_;
    double v_;
    double w_;
    double r_;
    double t1_;
    double centerX_;
    double centerY_;
};

// 类似球场的轨迹,start from 0
class CourtTrajectory
: public Trajectory
{
public:
    CourtTrajectory( double length = 1, double speed = 0.2, double r = 1 )
    : length_(length), speed_(speed), r_(r)
    {
        // caculate t1, t2, t3, t4
        t1_ = length_ / speed_;
        t2_ = t1_ + PI * r_ / speed_;
        t3_ = t2_ + length_ / speed_;
        t4_ = t3_ + PI * r_ / speed_;
        centerX1_ = length_;
        centerY1_ = r_;
        centerX2_ = 0;
        centerY2_ = r_;
        w_ = speed_ / r_;
        v_ = speed_;
    }

    virtual Location getLocation( double time ) override  
    {
        int n = time / t4_;
        double timeLeft = time - t4_ * n;
        if( timeLeft < t1_ )
        {
            double xr = speed_ * timeLeft;
            double yr = 0;
            double xr_dot = speed_;
            double yr_dot = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( timeLeft < t2_ )
        {
            double time1 = timeLeft - t1_;
            double xr = centerX1_ + r_ * sin( w_ * time1);
            double yr = centerY1_ - r_ * cos( w_ * time1);
            double xr_dot = v_ * cos( w_ * time1);
            double yr_dot = v_ * sin( w_ * time1);
            double thetar = getAngle(w_ * time1);
            return Location( xr, yr, thetar );
        }
        else if( timeLeft < t3_ )
        {
            double xr = speed_ * (t3_ - timeLeft);
            double yr = 2 * r_;
            double xr_dot = -speed_;
            double yr_dot = 0;
            double thetar = PI;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time1 = timeLeft - t3_;
            double xr = centerX2_ - r_ * sin( w_ * time1);
            double yr = centerY2_ + r_ * cos( w_ * time1);
            double xr_dot = - v_ * cos( w_ * time1);
            double yr_dot = - v_ * sin( w_ * time1);
            double thetar = getAngle(w_ * time1 + PI);
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        int n = time / t4_;
        double timeLeft = time - t4_ * n;
        if( timeLeft < t1_ )
        {
            double xr = speed_ * timeLeft;
            double yr = 0;
            double xr_dot = speed_;
            double yr_dot = 0;
            double thetar = 0;
            double vr = speed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( timeLeft < t2_ )
        {
            double time1 = timeLeft - t1_;
            double xr = centerX1_ + r_ * sin( w_ * time1);
            double yr = centerY1_ - r_ * cos( w_ * time1);
            double xr_dot = v_ * cos( w_ * time1);
            double yr_dot = v_ * sin( w_ * time1);
            double thetar = getAngle(w_ * time1);
            double vr = speed_;    
            double wr = w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( timeLeft < t3_ )
        {
            double xr = speed_ * (t3_ - timeLeft);
            double yr = 2 * r_;
            double xr_dot = - speed_;
            double yr_dot = 0;
            double thetar = PI;
            double vr = speed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time1 = timeLeft - t3_;
            double xr = centerX2_ - r_ * sin( w_ * time1);
            double yr = centerY2_ + r_ * cos( w_ * time1);
            double xr_dot = - v_ * cos( w_ * time1);
            double yr_dot = - v_ * sin( w_ * time1);
            double thetar = getAngle(w_ * time1 + PI);
            double vr = speed_;    
            double wr = w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }  

private:
    double length_;
    double speed_;
    double r_;
    double t1_, t2_, t3_, t4_;
    double centerX1_,centerY1_;
    double centerX2_, centerY2_;
    double v_, w_;
};


// 圆形轨迹，需要设置圆心和半径
class ReverseCircleTrajectory
:public Trajectory
{
public:
    ReverseCircleTrajectory(double x = 0, double y = 0, double theta = 0,
                    double r = 1.5, double speed = 0.2)
    : x_(x), y_(y), theta_(theta) , r_(r), speed_(speed)
    {
        centerX_ = x_ + r_ * sin(theta_);
        centerY_ = y_ - r_ * cos(theta_);
        w_ = speed_ / r_;
        v_ = speed_;
    }
    virtual Location getLocation( double time ) override
    {
        double xr = centerX_ + r_ * cos( theta_ + PI/2 - w_ * time );
        double yr = centerY_ + r_ * sin( theta_ + PI/2 - w_ * time );
        double xr_dot = v_ * sin( theta_ + PI/2 - w_ * time );
        double yr_dot = - v_ * cos( theta_ + PI/2 - w_ * time);
        double thetar = getAngle(theta_ - w_ * time);
        return Location( xr, yr, thetar );
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        double xr = centerX_ + r_ * cos( theta_ + PI/2 - w_ * time );
        double yr = centerY_ + r_ * sin( theta_ + PI/2 - w_ * time );
        double xr_dot = v_ * sin( theta_ + PI/2 - w_ * time );
        double yr_dot = - v_ * cos( theta_ + PI/2 - w_ * time);
        double thetar = getAngle(theta_ - w_ * time);
        double vr = speed_;    
        double wr = -w_;
        return PathInfo( xr,yr,thetar, wr, vr );
    }
private:
    // 根据原点位置和速度来进行
    double x_;
    double y_;
    double theta_;
    double r_;
    double speed_;
    double v_;
    double w_;
    double centerX_;
    double centerY_;
};


// J型轨迹
class ReverseJTypeTrajectory
: public Trajectory
{
    // 先直线然后在圆形
public:
    ReverseJTypeTrajectory(double x = 0, double y = 0, double theta = 0, double length = 1,
                    double speed = 0.2, double r = 1)
    : x_(x), y_(x), theta_(theta), length_(length), speed_(speed), r_(r)
    {
        centerX_ = x_ + length_ * cos(theta_) + r_ * sin(theta_);
        centerY_ = y_ + length_ * sin(theta_) - r_ * cos(theta_);
        t1_ = length_ / speed_;
        w_ = speed_ / r_;
        v_ = speed_;
    }

    virtual Location getLocation( double time ) override
    {
        if( time < t1_ )
        {
            double xr = x_ + speed_ * cos( theta_ ) * time;
            double yr = y_ + speed_ * sin( theta_ ) * time;
            double xr_dot = speed_ * cos( theta_ );
            double yr_dot = speed_ * sin( theta_ );
            double thetar = theta_;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( theta_ + PI/2 - w_ * time1 );
            double yr = centerY_ + r_ * sin( theta_ + PI/2 - w_ * time1 );
            double xr_dot = v_ * sin( theta_ + PI/2 - w_ * time1 );
            double yr_dot = - v_ * cos( theta_ + PI/2 - w_ * time1);
            double thetar = getAngle(theta_ - w_ * time1);
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        if( time < t1_ )
        {
            double xr = x_ + speed_ * cos( theta_ ) * time;
            double yr = y_ + speed_ * sin( theta_ ) * time;
            double xr_dot = speed_ * cos( theta_ );
            double yr_dot = speed_ * sin( theta_ );
            double thetar = theta_;
            double xr_dot_dot = 0;
            double yr_dot_dot = 0;
            double vr = speed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( theta_ + PI/2 - w_ * time1 );
            double yr = centerY_ + r_ * sin( theta_ + PI/2 - w_ * time1 );
            double xr_dot = v_ * sin( theta_ + PI/2 - w_ * time1 );
            double yr_dot = - v_ * cos( theta_ + PI/2 - w_ * time1);
            double thetar = getAngle(theta_ - w_ * time1);
            double vr = speed_;    
            double wr = - w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }
private:
    double x_;
    double y_;
    double theta_;
    double length_;
    double speed_;
    double v_;
    double w_;
    double r_;
    double t1_;
    double centerX_;
    double centerY_;
};


// 类似球场的轨迹,start from 0
class ReverseCourtTrajectory
: public Trajectory
{
public:
    ReverseCourtTrajectory( double length = 1, double speedLine = 0.3, double speedCircle = 0.2, double r = 1 )
    : length_(length), speedLine_(speedLine), r_(r), speedCircle_(speedCircle)
    {
        // caculate t1, t2, t3, t4
        t1_ = length_ / speedLine_;
        t2_ = t1_ + PI * r_ / speedCircle_;
        t3_ = t2_ + length_ / speedLine_;
        t4_ = t3_ + PI * r_ / speedCircle_;
        centerX1_ = length_;
        centerY1_ = - r_;
        centerX2_ = 0;
        centerY2_ = - r_;
        w_ = speedCircle_ / r_;
        vCircle_ = speedCircle_;
        vLine_ = speedLine_;
    }

    virtual Location getLocation( double time ) override  
    {
        int n = time / t4_;
        double timeLeft = time - t4_ * n;
        if( timeLeft < t1_ )
        {
            double xr = speedLine_ * timeLeft;
            double yr = 0;
            double xr_dot = speedLine_;
            double yr_dot = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( timeLeft < t2_ )
        {
            double time1 = timeLeft - t1_;
            double xr = centerX1_ + r_ * cos( PI/2 - w_ * time1 );
            double yr = centerY1_ + r_ * sin( PI/2 - w_ * time1 );
            double xr_dot = vCircle_ * sin( PI/2 - w_ * time1);
            double yr_dot = - vCircle_ * cos( PI/2 - w_ * time1);
            double thetar = getAngle(- w_ * time1);
            return Location( xr, yr, thetar );
        }
        else if( timeLeft < t3_ )
        {
            double xr = speedLine_ * (t3_ - timeLeft);
            double yr = - 2 * r_;
            double xr_dot = -speedLine_;
            double yr_dot = 0;
            double thetar = PI;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time1 = timeLeft - t3_;
            double xr = centerX2_ + r_ * cos( - w_ * time1 - PI / 2);
            double yr = centerY2_ + r_ * sin( - w_ * time1 - PI / 2);
            double xr_dot = vCircle_ * sin( - w_ * time1 - PI / 2);
            double yr_dot = - vCircle_ * cos( - w_ * time1 - PI / 2);
            double thetar = getAngle(- w_ * time1 - PI);
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        int n = time / t4_;
        double timeLeft = time - t4_ * n;
        if( timeLeft < t1_ )
        {
            double xr = speedLine_ * timeLeft;
            double yr = 0;
            double xr_dot = speedLine_;
            double yr_dot = 0;
            double thetar = 0;
            double vr = speedLine_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( timeLeft < t2_ )
        {
            double time1 = timeLeft - t1_;
            double xr = centerX1_ + r_ * cos( PI/2 - w_ * time1 );
            double yr = centerY1_ + r_ * sin( PI/2 - w_ * time1 );
            double xr_dot = vCircle_ * sin( PI/2 - w_ * time1);
            double yr_dot = - vCircle_ * cos( PI/2 - w_ * time1);
            double thetar = getAngle(- w_ * time1);
            double vr = speedCircle_;    
            double wr = - w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( timeLeft < t3_ )
        {
            double xr = speedLine_ * (t3_ - timeLeft);
            double yr = - 2 * r_;
            double xr_dot = - speedLine_;
            double yr_dot = 0;
            double thetar = PI;
            double vr = speedLine_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time1 = timeLeft - t3_;
            double xr = centerX2_ + r_ * cos( - w_ * time1 - PI / 2);
            double yr = centerY2_ + r_ * sin( - w_ * time1 - PI / 2);
            double xr_dot = vCircle_ * sin( - w_ * time1 - PI / 2);
            double yr_dot = - vCircle_ * cos( - w_ * time1 - PI / 2);
            double thetar = getAngle(- w_ * time1 - PI);
            double vr = speedCircle_;    
            double wr = - w_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }  

private:
    double length_;
    double speedLine_;
    double speedCircle_;
    double r_;
    double t1_, t2_, t3_, t4_;
    double centerX1_,centerY1_;
    double centerX2_, centerY2_;
    double vCircle_,vLine_, w_;
};

// 圆形轨迹，需要设置圆心和半径
class WeightTrajectory
:public Trajectory
{
public:
    WeightTrajectory()
    :ax0_(0), ax1_(0), ax2_(0), ax3_(0),
     ay0_(0), ay1_(0), ay2_(0), ay3_(0)
    {

    }

    void setWeights( vector<std_msgs::Float64>& weights )
    {
        ax0_ = weights[0].data;
        ay0_ = weights[1].data;
        ax1_ = weights[2].data;
        ay1_ = weights[3].data;
        ax2_ = weights[4].data;
        ay2_ = weights[5].data;
    }
    virtual Location getLocation( double time ) override
    {
        double xr = ax0_ + ax1_*time + ax2_*time*time + ax3_*time*time*time;
        double yr = ay0_ + ay1_*time + ay2_*time*time + ay3_*time*time*time;
        double xr_dot = ax1_ + 2*ax2_*time + 3*ax3_*time*time;
        double yr_dot = ay1_ + 2*ay2_*time + 3*ay3_*time*time;
        double thetar = atan2(yr_dot, xr_dot);
        return Location( xr, yr, thetar );
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        double xr = ax0_ + ax1_*time + ax2_*time*time + ax3_*time*time*time;
        double yr = ay0_ + ay1_*time + ay2_*time*time + ay3_*time*time*time;
        double xr_dot = ax1_ + 2*ax2_*time + 3*ax3_*time*time;
        double yr_dot = ay1_ + 2*ay2_*time + 3*ay3_*time*time;
        double thetar = atan2(yr_dot, xr_dot);
        double xr_dot_dot = 2*ax2_ + 6*ax3_*time;
        double yr_dot_dot = 2*ay2_ + 6*ay3_*time;
        double vr = sqrt(xr_dot*xr_dot + yr_dot*yr_dot);
        double wr = (xr_dot*yr_dot_dot - yr_dot*xr_dot_dot)/(vr*vr);
        return PathInfo( xr,yr,thetar, wr, vr );
    }
private:
    float ax0_, ax1_, ax2_, ax3_;
    float ay0_, ay1_, ay2_, ay3_;
};

class TurningRightTrajectory
:public Trajectory
{
private:
    double lineSpeed_;
    double length1_;
    double r_;
    double circleSpeed_;
    double circleAngle_;
    double length2_;
    double t1_;
    double t2_;
    double t3_;
    double w_;
    double centerX_,centerY_;
    double xStart_, yStart_;
    double angle_;
public:
    TurningRightTrajectory(double lineSpeed = 0.35, double length1 = 2, double r = 1.5,
                      double circleSpeed = 0.3, double circleAngle = PI/8, double length2 = 2)
    :lineSpeed_(lineSpeed), length1_(length1), r_(r), 
      circleSpeed_(circleSpeed), circleAngle_(circleAngle), length2_(length2)
    {
        t1_ = length1_ / lineSpeed_;
        t2_ = t1_ + 2 * r_ * circleAngle_ / circleSpeed_;
        t3_ = t2_ + length2_ / lineSpeed_;
        w_ = circleSpeed_ / r_;
        centerX_ = length1_;
        centerY_ = -r;
        xStart_ = centerX_ + r_ * cos( PI/2 - w_ * (t2_ - t1_) );
        yStart_ = centerY_ + r_ * sin( PI/2 - w_ * (t2_ - t1_) );
        angle_ = getAngle(- w_ * (t2_ - t1_));
    }

    virtual Location getLocation( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed_ * time;
            double yr = 0;
            double xr_dot = lineSpeed_;
            double yr_dot = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( PI/2 - w_ * time1 );
            double yr = centerY_ + r_ * sin( PI/2 - w_ * time1 );
            double thetar = getAngle(- w_ * time1);
            return Location( xr, yr, thetar );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time2;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time2;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time3 = t3_ - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time3;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed_ * time;
            double yr = 0;
            double thetar = 0;
            double vr = lineSpeed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( PI/2 - w_ * time1 );
            double yr = centerY_ + r_ * sin( PI/2 - w_ * time1 );
            double thetar = getAngle(- w_ * time1);
            double wr = - w_;
            double vr = circleSpeed_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time2;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time2;
            double thetar = angle_;
            double wr = 0;
            double vr = lineSpeed_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time3 = t3_ - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time3;
            double thetar = angle_;
            double wr = 0;
            double vr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }
};

class TurningLeftTrajectory
:public Trajectory
{
private:
    double lineSpeed_;
    double length1_;
    double r_;
    double circleSpeed_;
    double circleAngle_;
    double length2_;
    double t1_;
    double t2_;
    double t3_;
    double w_;
    double centerX_,centerY_;
    double xStart_, yStart_;
    double angle_;
public:
    TurningLeftTrajectory(double lineSpeed = 0.35, double length1 = 2, double r = 1.5,
                      double circleSpeed = 0.3, double circleAngle = PI/8, double length2 = 2)
    :lineSpeed_(lineSpeed), length1_(length1), r_(r), 
      circleSpeed_(circleSpeed), circleAngle_(circleAngle), length2_(length2)
    {
        t1_ = length1_ / lineSpeed_;
        t2_ = t1_ + 2 * r_ * circleAngle_ / circleSpeed_;
        t3_ = t2_ + length2_ / lineSpeed_;
        w_ = circleSpeed_ / r_;
        centerX_ = length1_;
        centerY_ = r;
        xStart_ = centerX_ + r_ * cos( - PI/2 + w_ * (t2_ - t1_) );
        yStart_ = centerY_ + r_ * sin( - PI/2 + w_ * (t2_ - t1_) );
        angle_ = getAngle( w_ * (t2_ - t1_));
    }

    virtual Location getLocation( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed_ * time;
            double yr = 0;
            double xr_dot = lineSpeed_;
            double yr_dot = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( - PI/2 + w_ * time1 );
            double yr = centerY_ + r_ * sin( - PI/2 + w_ * time1 );
            double thetar = getAngle( w_ * time1);
            return Location( xr, yr, thetar );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time2;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time2;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time3 = t3_ - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time3;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed_ * time;
            double yr = 0;
            double thetar = 0;
            double vr = lineSpeed_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = centerX_ + r_ * cos( - PI/2 + w_ * time1 );
            double yr = centerY_ + r_ * sin( - PI/2 + w_ * time1 );
            double thetar = getAngle( w_ * time1);
            double wr =  w_;
            double vr = circleSpeed_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time2;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time2;
            double thetar = angle_;
            double wr = 0;
            double vr = lineSpeed_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time3 = t3_ - t2_;
            double xr = xStart_ + lineSpeed_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed_ * sin( angle_ ) * time3;
            double thetar = angle_;
            double wr = 0;
            double vr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }
};


class TurningLeftTrajectory2
:public Trajectory
{
private:
    double lineSpeed1_;
    double lineSpeed2_;
    double length1_;
    double length2_;
    double length3_;
    double r_;
    double circleSpeed_;
    double circleAngle_;
    double t1_;
    double t2_;
    double t3_;
    double t4_;
    double w_;
    double centerX_,centerY_;
    double xStart_, yStart_;
    double angle_;
public:
    TurningLeftTrajectory2(double lineSpeed1 = 0.2, double lineSpeed2 = 0.3, double length1 = 0.5, double length2 = 0.5, double r = 3,
                      double circleSpeed = 0.3, double circleAngle = PI/9, double length3 = 3)
    :lineSpeed1_(lineSpeed1), lineSpeed2_(lineSpeed2), length1_(length1), length2_(length2), r_(r), 
      circleSpeed_(circleSpeed), circleAngle_(circleAngle), length3_(length3)
    {
        t1_ = length1_ / lineSpeed1_;
        t2_ = t1_ + length2_ / lineSpeed2_;
        t3_ = t2_ + 2 * r_ * circleAngle_ / circleSpeed_;
        t4_ = t3_ + length3_ / lineSpeed2_;
        w_ = circleSpeed_ / r_;
        centerX_ = length1_ + length2_;
        centerY_ = r;
        xStart_ = centerX_ + r_ * cos( - PI/2 + w_ * (t3_ - t2_) );
        yStart_ = centerY_ + r_ * sin( - PI/2 + w_ * (t3_ - t2_) );
        angle_ = getAngle( w_ * (t3_ - t2_));
    }

    virtual Location getLocation( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed1_ * time;
            double yr = 0;
            double xr_dot = lineSpeed1_;
            double yr_dot = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = length1_ + lineSpeed2_ * time1;
            double yr = 0;
            double thetar = 0;
            return Location( xr, yr, thetar );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = centerX_ + r_ * cos( - PI/2 + w_ * time2 );
            double yr = centerY_ + r_ * sin( - PI/2 + w_ * time2 );
            double thetar = getAngle( w_ * time2);
            return Location( xr, yr, thetar );
        }
        else if( time < t4_ )
        {
            double time3 = time - t3_;
            double xr = xStart_ + lineSpeed2_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed2_ * sin( angle_ ) * time3;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
        else
        {
            double time3 = t4_ - t3_;
            double xr = xStart_ + lineSpeed2_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed2_ * sin( angle_ ) * time3;
            double thetar = angle_;
            return Location( xr, yr, thetar );
        }
    }

    virtual PathInfo getPathInfo( double time ) override
    {
        if( time < t1_ )
        {
            double xr = lineSpeed1_ * time;
            double yr = 0;
            double thetar = 0;
            double vr = lineSpeed1_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t2_ )
        {
            double time1 = time - t1_;
            double xr = length1_ + lineSpeed2_ * time1;
            double yr = 0;
            double thetar = 0;
            double vr = lineSpeed2_;    
            double wr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t3_ )
        {
            double time2 = time - t2_;
            double xr = centerX_ + r_ * cos( - PI/2 + w_ * time2 );
            double yr = centerY_ + r_ * sin( - PI/2 + w_ * time2 );
            double thetar = getAngle( w_ * time2);
            double wr =  w_;
            double vr = circleSpeed_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else if( time < t4_ )
        {
            double time3 = time - t3_;
            double xr = xStart_ + lineSpeed2_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed2_ * sin( angle_ ) * time3;
            double thetar = angle_;
            double wr = 0;
            double vr = lineSpeed2_;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
        else
        {
            double time3 = t4_ - t3_;
            double xr = xStart_ + lineSpeed2_ * cos( angle_ ) * time3;
            double yr = yStart_ + lineSpeed2_ * sin( angle_ ) * time3;
            double thetar = angle_;
            double wr = 0;
            double vr = 0;
            return PathInfo( xr,yr,thetar, wr, vr );
        }
    }
};