FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/eddiebot_node/msg"
  "../src/eddiebot_node/srv"
  "CMakeFiles/rosbuild_clean-test-results"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rosbuild_clean-test-results.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
