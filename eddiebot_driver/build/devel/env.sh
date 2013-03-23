#!/usr/bin/env sh
# generated from catkin/cmake/templates/env.sh.in

if [ $# -eq 0 ] ; then
  /bin/echo "Entering environment at '/opt/ros/groovy/stacks/eddiebot/eddiebot/eddiebot_driver/build/devel', type 'exit' to leave"
  . "/opt/ros/groovy/stacks/eddiebot/eddiebot/eddiebot_driver/build/devel/setup.sh"
  "$SHELL" -i
  /bin/echo "Exiting environment at '/opt/ros/groovy/stacks/eddiebot/eddiebot/eddiebot_driver/build/devel'"
else
  . "/opt/ros/groovy/stacks/eddiebot/eddiebot/eddiebot_driver/build/devel/setup.sh"
  exec "$@"
fi
