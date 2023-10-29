
add_executable (SPI-Transmit
  SPI_Transmit.c
  slave_objectlist.c
  )
target_link_libraries(SPI-Transmit LINK_PUBLIC soes bcm2835)
install (TARGETS SPI-Transmit DESTINATION sbin)
install (PROGRAMS S60soes DESTINATION /etc/init.d)
