#include "test_impl.hpp"

#include <cstdint>


ParserTest::ParserTest()
{
  // make property
  property.accFsr   = 2;
  property.gyroFsr  = 2000;
  property.magXcoef = 0;
  property.magYcoef = 0;
  property.magZcoef = 0;

  // make test_data
  for (int i = 0; i < c_packet_size; i++) {
    test_data[i].ax = 0;
    test_data[i].ay = 1;
    test_data[i].az =
        static_cast<std::int16_t>((static_cast<std::int32_t>(INT16_MAX)) / 2);

    test_data[i].gx = static_cast<std::int16_t>(
        (static_cast<std::int32_t>(INT16_MAX) + 1) / 2);

    test_data[i].gy = INT16_MAX - 1;
    test_data[i].gz = INT16_MAX;

    test_data[i].mx = 0;
    test_data[i].my = 0;
    test_data[i].mz = 0;
  }

  // make test_byteArray_data
  char *temp = reinterpret_cast<char *>(test_data);
  for (int i = 0; i < c_data_size; i++) {
    test_byteArray_data[i] = *(temp + i);
  }
}


ParserTest::~ParserTest() {}


TEST_F(ParserTest, test1)
{
  auto parser = Parser{property};
  auto data =
      parser.parse(reinterpret_cast<std::uint8_t *>(test_byteArray_data));

  EXPECT_EQ(0, data[0].ax);
}
