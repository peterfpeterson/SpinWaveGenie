ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(SublatticeTest SublatticeTest.cpp)
target_link_libraries( SublatticeTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(CellTest CellTest.cpp )
target_link_libraries( CellTest ${Boost_LIBRARIES} SpinWaveGenie) 
add_executable(FormFactorTest FormFactorTest.cpp )
target_link_libraries( FormFactorTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(HKLDirectionsTest HKLDirectionsTest.cpp )
target_link_libraries( HKLDirectionsTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(EnergiesTest EnergiesTest.cpp )
target_link_libraries( EnergiesTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(ResultsTest ResultsTest.cpp )
target_link_libraries( ResultsTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(ThreeVectorsTest ThreeVectorsTest.cpp )
target_link_libraries( ThreeVectorsTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(UniqueThreeVectorsTest UniqueThreeVectorsTest.cpp )
target_link_libraries( UniqueThreeVectorsTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(PointsAlongLineTest PointsAlongLineTest.cpp)
target_link_libraries( PointsAlongLineTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(NeighborsTest NeighborsTest.cpp)
target_link_libraries( NeighborsTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(MagneticFieldInteractionTest MagneticFieldInteractionTest.cpp)
target_link_libraries( MagneticFieldInteractionTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(EnergyResolutionFunctionTest EnergyResolutionFunctionTest.cpp)
target_link_libraries( EnergyResolutionFunctionTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(IntegrateThetaPhiTest IntegrateThetaPhiTest.cpp)
target_link_libraries( IntegrateThetaPhiTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(IntegrateEnergyTest IntegrateEnergyTest.cpp)
target_link_libraries( IntegrateEnergyTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(AdaptiveSimpsonTest AdaptiveSimpsonTest.cpp)
target_link_libraries( AdaptiveSimpsonTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(FMDispersionTest FMDispersionTest.cpp)
target_link_libraries( FMDispersionTest ${Boost_LIBRARIES} SpinWaveGenie)
add_executable(AFMDispersionTest AFMDispersionTest.cpp)
target_link_libraries( AFMDispersionTest ${Boost_LIBRARIES} SpinWaveGenie)

add_test(NAME SublatticeTest COMMAND ${EXECUTABLE_OUTPUT_PATH}/SublatticeTest)
add_test(NAME CellTest COMMAND CellTest)
add_test(NAME FormFactorTest COMMAND FormFactorTest)
add_test(NAME HKLDirectionsTest COMMAND HKLDirectionsTest)
add_test(NAME EnergiesTest COMMAND EnergiesTest)
add_test(NAME ResultsTest COMMAND ResultsTest)
add_test(NAME ThreeVectorsTest COMMAND ThreeVectorsTest )
add_test(NAME UniqueThreeVectorsTest COMMAND UniqueThreeVectorsTest )
add_test(NAME PointsAlongLineTest COMMAND PointsAlongLineTest)
add_test(NAME NeighborsTest COMMAND NeighborsTest)
add_test(NAME MagneticFieldInteractionTest COMMAND MagneticFieldInteractionTest)
add_test(NAME EnergyResolutionFunctionTest COMMAND EnergyResolutionFunctionTest)
add_test(NAME IntegrateThetaPhiTest COMMAND IntegrateThetaPhiTest)
add_test(NAME IntegrateEnergyTest COMMAND IntegrateEnergyTest)
add_test(NAME AdaptiveSimpsonTest COMMAND AdaptiveSimpsonTest)
add_test(NAME FMDispersionTest COMMAND FMDispersionTest)
add_test(NAME AFMDispersionTest COMMAND AFMDispersionTest)
