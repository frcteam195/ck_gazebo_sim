/*
 * Copyright (C) 2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef GAZEBO_PLUGINS_FRC2016GAMEPLUGIN_HH_
#define GAZEBO_PLUGINS_FRC2016GAMEPLUGIN_HH_

#include <vector>
#include <ignition/math/Box.hh>
#include <ignition/transport/Node.hh>

#include <gazebo/common/Event.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo
{
  /// \brief A plugin that control the FRC 2016 game world.
  class GAZEBO_VISIBLE FRC2016Plugin : public WorldPlugin
  {
    // The two teams
    enum Team {BLUE = 0, RED, TEAM_COUNT};

    /// \brief Constructor.
    public: FRC2016Plugin();

    // Documentation inherited
    public: virtual void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);

    /// \brief Callback for World Update events.
    private: void OnUpdate();

    private: void UpdateCastleBalls(const physics::Model_V &_models);

    private: void LaunchBall(const physics::ModelPtr _model, Team _side);

    private: void GoalVisuals();
    private: void UpdateScore();

    /// \brief World pointer.
    private: physics::WorldPtr world;

    /// \brief Connection to World Update events.
    private: event::ConnectionPtr updateConnection;

    private: class GateData
             {
               public: bool active = false;
               public: ignition::math::Pose3d entered =
                       ignition::math::Pose3d::Zero;
             };

    // An individual gate, used for scoring points when a robot crosses
    // an obstacle.
    private: class Gate
             {
               public: Gate(const ignition::math::Box &_box, const Team _team)
                       : box(_box), team(_team) {}

               public: ignition::math::Box box;
               public: Team team;
               public: int crossedCount = 0;
             };

    private: class Turret
             {
               public: Turret(Team _team,
                           const ignition::math::Box &_upperGoal,
                           const ignition::math::Box &_lowerGoal)
                       : team(_team), upperGoal(_upperGoal),
                         lowerGoal(_lowerGoal)
                       {
                       }

               public: Team team;
               public: ignition::math::Box upperGoal;
               public: ignition::math::Box lowerGoal;
             };

    // All the gates that generate points when a robot cross them.
    private: std::vector<Gate> gates;

    private: std::vector<Turret> turrets;
    private: std::map<Team, ignition::math::Pose3d> ballBin;

    private: std::map<std::string, GateData> inGate;

    // These two planes are used to check if a robot crossed of a boundary
    private: std::array<ignition::math::Planed, TEAM_COUNT> planes;

    private: std::vector<std::string> gamePieces;

    // Names of the red and blue robots
    private: std::array<std::vector<std::string>, TEAM_COUNT> robots
             {{{"blue_robot_1", "blue_robot_2", "blue_robot_3"},
               {"red_robot_1", "red_robot_2", "red_robot_3"}}};

    private: std::array<int, TEAM_COUNT> score{{0, 0}};

    private: std::array<common::Time, TEAM_COUNT> launchTimes;
    private: std::array<ignition::math::Pose3d, TEAM_COUNT> launchPoses;

    private: std::array<std::string, 2> teamNames{{"Red", "Blue"}};

    private: ignition::transport::Node node;
    private: ignition::transport::Node::PublisherId markerPub;

    private: ignition::transport::Node::PublisherId scorePubId;
  };
}

#endif
