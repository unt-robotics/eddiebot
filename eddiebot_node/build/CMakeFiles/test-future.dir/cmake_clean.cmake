FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/eddiebot_node/msg"
  "../src/eddiebot_node/srv"
  "CMakeFiles/test-future"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/test-future.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
