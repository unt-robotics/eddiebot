//#line 2 "/opt/ros/groovy/share/dynamic_reconfigure/templates/ConfigType.h"
// *********************************************************
// 
// File autogenerated for the eddiebot_node package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

/***********************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ***********************************************************/

// Author: Blaise Gassend


#ifndef __eddiebot_node__EDDIEBOTCONFIG_H__
#define __eddiebot_node__EDDIEBOTCONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace eddiebot_node
{
  class EddieBotConfigStatics;
  
  class EddieBotConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(EddieBotConfig &config, const EddieBotConfig &max, const EddieBotConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const EddieBotConfig &config1, const EddieBotConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, EddieBotConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const EddieBotConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, EddieBotConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const EddieBotConfig &config) const = 0;
      virtual void getValue(const EddieBotConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T EddieBotConfig::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (EddieBotConfig::* field);

      virtual void clamp(EddieBotConfig &config, const EddieBotConfig &max, const EddieBotConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const EddieBotConfig &config1, const EddieBotConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, EddieBotConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const EddieBotConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, EddieBotConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const EddieBotConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const EddieBotConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, EddieBotConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); i++)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string name, std::string type, int parent, int id, bool s, T PT::* f) : AbstractGroupDescription(name, type, parent, id, s), field(f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;
        
        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++) 
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }
      
      virtual void updateParams(boost::any &cfg, EddieBotConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++) 
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<EddieBotConfig::AbstractGroupDescriptionConstPtr> groups;
    };
    
class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(EddieBotConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = params.begin(); i != params.end(); i++)
      {
        boost::any val;
        (*i)->getValue(config, val);

        if("update_rate"==(*i)->name){update_rate = boost::any_cast<double>(val);}
        if("drive_mode"==(*i)->name){drive_mode = boost::any_cast<std::string>(val);}
        if("cmd_vel_timeout"==(*i)->name){cmd_vel_timeout = boost::any_cast<double>(val);}
        if("stop_motors_on_bump"==(*i)->name){stop_motors_on_bump = boost::any_cast<bool>(val);}
        if("has_gyro"==(*i)->name){has_gyro = boost::any_cast<bool>(val);}
        if("gyro_scale_correction"==(*i)->name){gyro_scale_correction = boost::any_cast<double>(val);}
        if("gyro_measurement_range"==(*i)->name){gyro_measurement_range = boost::any_cast<double>(val);}
        if("odom_angular_scale_correction"==(*i)->name){odom_angular_scale_correction = boost::any_cast<double>(val);}
        if("odom_linear_scale_correction"==(*i)->name){odom_linear_scale_correction = boost::any_cast<double>(val);}
        if("min_abs_yaw_vel"==(*i)->name){min_abs_yaw_vel = boost::any_cast<double>(val);}
        if("max_abs_yaw_vel"==(*i)->name){max_abs_yaw_vel = boost::any_cast<double>(val);}
      }
    }

    double update_rate;
std::string drive_mode;
double cmd_vel_timeout;
bool stop_motors_on_bump;
bool has_gyro;
double gyro_scale_correction;
double gyro_measurement_range;
double odom_angular_scale_correction;
double odom_linear_scale_correction;
double min_abs_yaw_vel;
double max_abs_yaw_vel;

    bool state;
    std::string name;

    
}groups;



//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double update_rate;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      std::string drive_mode;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double cmd_vel_timeout;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      bool stop_motors_on_bump;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      bool has_gyro;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double gyro_scale_correction;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double gyro_measurement_range;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double odom_angular_scale_correction;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double odom_linear_scale_correction;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double min_abs_yaw_vel;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      double max_abs_yaw_vel;
//#line 255 "/opt/ros/groovy/share/dynamic_reconfigure/templates/ConfigType.h"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("EddieBotConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }
    
    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const EddieBotConfig &__max__ = __getMax__();
      const EddieBotConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const EddieBotConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const EddieBotConfig &__getDefault__();
    static const EddieBotConfig &__getMax__();
    static const EddieBotConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();
    
  private:
    static const EddieBotConfigStatics *__get_statics__();
  };
  
  template <> // Max and min are ignored for strings.
  inline void EddieBotConfig::ParamDescription<std::string>::clamp(EddieBotConfig &config, const EddieBotConfig &max, const EddieBotConfig &min) const
  {
    return;
  }

  class EddieBotConfigStatics
  {
    friend class EddieBotConfig;
    
    EddieBotConfigStatics()
    {
EddieBotConfig::GroupDescription<EddieBotConfig::DEFAULT, EddieBotConfig> Default("Default", "", 0, 0, true, &EddieBotConfig::groups);
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.update_rate = 60.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.update_rate = 30.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.update_rate = 30.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("update_rate", "double", 0, "Polling rate for the parallax eddie.", "", &EddieBotConfig::update_rate)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("update_rate", "double", 0, "Polling rate for the parallax eddie.", "", &EddieBotConfig::update_rate)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.drive_mode = "";
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.drive_mode = "";
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.drive_mode = "twist";
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<std::string>("drive_mode", "str", 0, "The possible drive modes (twist, eddie, drive).", "{'enum_description': '', 'enum': [{'srcline': 11, 'description': 'Takes a geometry_msgs/Twist message and is navigation compatible.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'twist', 'ctype': 'std::string', 'type': 'str', 'name': 'twist'}, {'srcline': 12, 'description': 'Takes a eddiebot_node/Eddie message and is eddiesim compatible.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'eddie', 'ctype': 'std::string', 'type': 'str', 'name': 'eddie'}, {'srcline': 13, 'description': 'Takes a eddiebot_node/Drive message which drives the EddieBot as described in the Parallax Eddie manual.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'drive', 'ctype': 'std::string', 'type': 'str', 'name': 'drive'}]}", &EddieBotConfig::drive_mode)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<std::string>("drive_mode", "str", 0, "The possible drive modes (twist, eddie, drive).", "{'enum_description': '', 'enum': [{'srcline': 11, 'description': 'Takes a geometry_msgs/Twist message and is navigation compatible.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'twist', 'ctype': 'std::string', 'type': 'str', 'name': 'twist'}, {'srcline': 12, 'description': 'Takes a eddiebot_node/Eddie message and is eddiesim compatible.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'eddie', 'ctype': 'std::string', 'type': 'str', 'name': 'eddie'}, {'srcline': 13, 'description': 'Takes a eddiebot_node/Drive message which drives the EddieBot as described in the Parallax Eddie manual.', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const char * const', 'value': 'drive', 'ctype': 'std::string', 'type': 'str', 'name': 'drive'}]}", &EddieBotConfig::drive_mode)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.cmd_vel_timeout = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.cmd_vel_timeout = 0.5;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.cmd_vel_timeout = 0.5;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("cmd_vel_timeout", "double", 0, "How long to wait before timing out on a velocity command..", "", &EddieBotConfig::cmd_vel_timeout)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("cmd_vel_timeout", "double", 0, "How long to wait before timing out on a velocity command..", "", &EddieBotConfig::cmd_vel_timeout)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.stop_motors_on_bump = 0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.stop_motors_on_bump = 1;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.stop_motors_on_bump = 1;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<bool>("stop_motors_on_bump", "bool", 0, "Stops motors when the bumps sensor is hit.", "", &EddieBotConfig::stop_motors_on_bump)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<bool>("stop_motors_on_bump", "bool", 0, "Stops motors when the bumps sensor is hit.", "", &EddieBotConfig::stop_motors_on_bump)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.has_gyro = 0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.has_gyro = 1;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.has_gyro = 1;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<bool>("has_gyro", "bool", 0, "Enables or disables the gyro.", "", &EddieBotConfig::has_gyro)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<bool>("has_gyro", "bool", 0, "Enables or disables the gyro.", "", &EddieBotConfig::has_gyro)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.gyro_scale_correction = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.gyro_scale_correction = 6.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.gyro_scale_correction = 1.35;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("gyro_scale_correction", "double", 0, "Scaling factor for correct gyro operation.", "", &EddieBotConfig::gyro_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("gyro_scale_correction", "double", 0, "Scaling factor for correct gyro operation.", "", &EddieBotConfig::gyro_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.gyro_measurement_range = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.gyro_measurement_range = 300.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.gyro_measurement_range = 150.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("gyro_measurement_range", "double", 0, "Measurement range supported by gyro.", "{'enum_description': 'Gyro Options', 'enum': [{'srcline': 25, 'description': 'ADXRS613 150deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 150.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS613'}, {'srcline': 26, 'description': 'ADXRS652 250deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 250.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS652'}, {'srcline': 27, 'description': 'ADXRS642 300deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 300.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS642'}]}", &EddieBotConfig::gyro_measurement_range)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("gyro_measurement_range", "double", 0, "Measurement range supported by gyro.", "{'enum_description': 'Gyro Options', 'enum': [{'srcline': 25, 'description': 'ADXRS613 150deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 150.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS613'}, {'srcline': 26, 'description': 'ADXRS652 250deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 250.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS652'}, {'srcline': 27, 'description': 'ADXRS642 300deg/s', 'srcfile': '../cfg/EddieBot.cfg', 'cconsttype': 'const double', 'value': 300.0, 'ctype': 'double', 'type': 'double', 'name': 'ADXRS642'}]}", &EddieBotConfig::gyro_measurement_range)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.odom_angular_scale_correction = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.odom_angular_scale_correction = 3.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.odom_angular_scale_correction = 1.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("odom_angular_scale_correction", "double", 0, "A correction applied to the computation of the rotation in the odometry.", "", &EddieBotConfig::odom_angular_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("odom_angular_scale_correction", "double", 0, "A correction applied to the computation of the rotation in the odometry.", "", &EddieBotConfig::odom_angular_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.odom_linear_scale_correction = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.odom_linear_scale_correction = 3.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.odom_linear_scale_correction = 1.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("odom_linear_scale_correction", "double", 0, "A correction applied to the computation of the translation in odometry.", "", &EddieBotConfig::odom_linear_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("odom_linear_scale_correction", "double", 0, "A correction applied to the computation of the translation in odometry.", "", &EddieBotConfig::odom_linear_scale_correction)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.min_abs_yaw_vel = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.min_abs_yaw_vel = 3.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.min_abs_yaw_vel = 0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("min_abs_yaw_vel", "double", 0, "Minimum angular velocity of the EddieBot.", "", &EddieBotConfig::min_abs_yaw_vel)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("min_abs_yaw_vel", "double", 0, "Minimum angular velocity of the EddieBot.", "", &EddieBotConfig::min_abs_yaw_vel)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __min__.max_abs_yaw_vel = 0.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __max__.max_abs_yaw_vel = 3.0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __default__.max_abs_yaw_vel = 0;
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("max_abs_yaw_vel", "double", 0, "Maximum angular velocity of the EddieBot.", "", &EddieBotConfig::max_abs_yaw_vel)));
//#line 259 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(EddieBotConfig::AbstractParamDescriptionConstPtr(new EddieBotConfig::ParamDescription<double>("max_abs_yaw_vel", "double", 0, "Maximum angular velocity of the EddieBot.", "", &EddieBotConfig::max_abs_yaw_vel)));
//#line 233 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      Default.convertParams();
//#line 233 "/opt/ros/groovy/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator.py"
      __group_descriptions__.push_back(EddieBotConfig::AbstractGroupDescriptionConstPtr(new EddieBotConfig::GroupDescription<EddieBotConfig::DEFAULT, EddieBotConfig>(Default)));
//#line 390 "/opt/ros/groovy/share/dynamic_reconfigure/templates/ConfigType.h"
    
      for (std::vector<EddieBotConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__); 
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__); 
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__); 
    }
    std::vector<EddieBotConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<EddieBotConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    EddieBotConfig __max__;
    EddieBotConfig __min__;
    EddieBotConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const EddieBotConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static EddieBotConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &EddieBotConfig::__getDescriptionMessage__() 
  {
    return __get_statics__()->__description_message__;
  }

  inline const EddieBotConfig &EddieBotConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }
  
  inline const EddieBotConfig &EddieBotConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }
  
  inline const EddieBotConfig &EddieBotConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }
  
  inline const std::vector<EddieBotConfig::AbstractParamDescriptionConstPtr> &EddieBotConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<EddieBotConfig::AbstractGroupDescriptionConstPtr> &EddieBotConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const EddieBotConfigStatics *EddieBotConfig::__get_statics__()
  {
    const static EddieBotConfigStatics *statics;
  
    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = EddieBotConfigStatics::get_instance();
    
    return statics;
  }

//#line 11 "../cfg/EddieBot.cfg"
      const char * const EddieBot_twist = "twist";
//#line 12 "../cfg/EddieBot.cfg"
      const char * const EddieBot_eddie = "eddie";
//#line 13 "../cfg/EddieBot.cfg"
      const char * const EddieBot_drive = "drive";
//#line 25 "../cfg/EddieBot.cfg"
      const double EddieBot_ADXRS613 = 150.0;
//#line 26 "../cfg/EddieBot.cfg"
      const double EddieBot_ADXRS652 = 250.0;
//#line 27 "../cfg/EddieBot.cfg"
      const double EddieBot_ADXRS642 = 300.0;
}

#endif // __EDDIEBOTRECONFIGURATOR_H__
