#include <test.h>

#include <granules.h>

/*
char *GenTimeKey(time_t now);
const char *ShiftSlotToString(int shift_slot);
int GetTimeSlot(time_t here_and_now);
int GetShiftSlot(time_t here_and_now);

time_t GetShiftSlotStart(time_t t);
time_t MeasurementSlotStart(time_t t);
time_t MeasurementSlotTime(size_t slot, size_t num_slots, time_t now);
*/

static void test_get_time_slot(void)
{
    assert_int_equal(0, GetTimeSlot(1325462400)); // monday 00:00
    assert_int_equal(1152, GetTimeSlot(1325808000)); // friday 00:00
    assert_int_equal(2015, GetTimeSlot(1326067020)); // sunday 23:57
}

static void test_measurement_slot_start(void)
{
    assert_int_equal(1326066900, MeasurementSlotStart(1326067020)); // sunday 23:57 -> 23:55
}

static void test_measurement_slot_time(void)
{
    static const time_t now = 1326066900; // sunday 23:55
    assert_int_equal(1325462400, MeasurementSlotTime(0, 2016, now)); // monday 00:00
    assert_int_equal(1325808000, MeasurementSlotTime(1152, 2016, now)); // friday 00:00
    assert_int_equal(1326066900, MeasurementSlotTime(2015, 2016, now)); // sunday 23:55
}

static void test_gen_time_key(void)
{
    assert_string_equal("Mon:Hr00:Min00_05", GenTimeKey(1325462400));
    assert_string_equal("Mon:Hr00:Min00_05", GenTimeKey(1325462460));
    assert_string_equal("Mon:Hr00:Min00_05", GenTimeKey(1325462520));
    assert_string_equal("Mon:Hr00:Min00_05", GenTimeKey(1325462580));
    assert_string_equal("Mon:Hr00:Min00_05", GenTimeKey(1325462640));

    assert_string_equal("Mon:Hr00:Min05_10", GenTimeKey(1325462700));
    assert_string_equal("Mon:Hr00:Min05_10", GenTimeKey(1325462760));
    assert_string_equal("Mon:Hr00:Min05_10", GenTimeKey(1325462820));
    assert_string_equal("Mon:Hr00:Min05_10", GenTimeKey(1325462880));
    assert_string_equal("Mon:Hr00:Min05_10", GenTimeKey(1325462940));
}

int main()
{
    const UnitTest tests[] =
    {
        unit_test(test_get_time_slot),
        unit_test(test_measurement_slot_start),
        unit_test(test_measurement_slot_time),
        unit_test(test_gen_time_key)
    };

    PRINT_TEST_BANNER();
    return run_tests(tests);
}
