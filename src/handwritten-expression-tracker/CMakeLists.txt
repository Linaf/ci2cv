SET(HEADERS_ONE expressiondetection.cpp)
SET(HEADERS_TWO expressiondetection.h)
add_executable(handwritten-expression-tracker main.cpp ${HEADERS_ONE} ${HEADERS_TWO})
target_link_libraries(handwritten-expression-tracker 
  utilities
  clmTracker
  ${LIBS})
