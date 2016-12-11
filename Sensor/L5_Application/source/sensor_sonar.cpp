/*
 * sensor.cpp
 *
 *  Created on: Oct 18, 2016
 *      Author: BHUSHAN
 *
 *      PIN CONNECTIONS:
 *      Left: PW:2.5  RX:1.28
 *      Middle: PW:2.3 RX:1.23
 *      Right:  PW:2.1 RX: 1.22
 *      Rear:  PW:2.7 RX:1.29
 */
#include <sensor_sonar.hpp>

#include "eint.h"
#include "tasks.hpp"
#include "shared_handles.h"
#include "scheduler_task.hpp"
#include "can.h"
#include "lpc_timers.h"
#include <stdint.h>
#include "utilities.h"
#include "_can_dbc/generated_can.h"
#include "io.hpp"
#include "stdio.h"
#include "string.h"

#define TIMER_TICK 1

sensor_readings obstacle;

static int start_time_middle=0, actual_time_middle = 0;
static int start_time_right=0, actual_time_right =0;
static int start_time_left=0, actual_time_left = 0;
static int start_time_rear=0, actual_time_rear =0;


SENSOR_HEARTBEAT_t sensor_heartbeat_message = {0};
//can_msg_t can_msg_sensor = { 0 };
can_msg_t can_msg_received;
can_msg_t can_msg = { 0 };

const uint32_t MASTER_SYSTEM_CMD__MIA_MS = 1000;
const MASTER_SYSTEM_CMD_t MASTER_SYSTEM_CMD__MIA_MSG = {SYSTEM_STOP};

SENSOR_ULTRASONIC_t ultrasonic_sensor_data = {0};


MASTER_SYSTEM_CMD_t master_command;

dbc_mia_info_t mia_handling = {0};

SENSOR_BATT_t battery_status = {0};

dbc_msg_hdr_t can_msg_hdr;

static int counter = 0;

void decoded_can_sensor_message(uint8_t middle,uint8_t left, uint8_t right,uint8_t rear, uint8_t critical)
{

    ultrasonic_sensor_data.SENSOR_ULTRASONIC_middle = middle;
    ultrasonic_sensor_data.SENSOR_ULTRASONIC_left = left;
    ultrasonic_sensor_data.SENSOR_ULTRASONIC_right = right;
    ultrasonic_sensor_data.SENSOR_ULTRASONIC_rear = rear;
    ultrasonic_sensor_data.SENSOR_ULTRASONIC_critical=critical;
    dbc_encode_and_send_SENSOR_ULTRASONIC(&ultrasonic_sensor_data);

}


bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{

    can_msg.msg_id = mid;
    can_msg.frame_fields.data_len = dlc;
    memcpy(can_msg.data.bytes, bytes, dlc);
    return CAN_tx(can1, &can_msg, 0);
}

void ultrasonic_sensor_heartbeat_message()
{
    sensor_heartbeat_message.SENSOR_HEARTBEAT_tx_bytes = 12;
    sensor_heartbeat_message.SENSOR_HEARTBEAT_rx_bytes = 54;
    dbc_encode_and_send_SENSOR_HEARTBEAT(&sensor_heartbeat_message);
}


void isr_middle1()
{
    // puts("inside isr_middle1 \n");
    actual_time_middle = lpc_timer_get_value(lpc_timer0) - start_time_middle;
    obstacle.middle_distance = actual_time_middle / 147;
    portYIELD_FROM_ISR(0);
}

void isr_right1()
{
    // puts("inside isr_right1 \n");
    actual_time_right = lpc_timer_get_value(lpc_timer0) - start_time_right;
    obstacle.right_distance = actual_time_right / 147;

    portYIELD_FROM_ISR(0);
}
void isr_left1()
{
    // puts("inside isr_left1 \n");
    actual_time_left = lpc_timer_get_value(lpc_timer0) - start_time_left;
    obstacle.left_distance = actual_time_left / 147;

    portYIELD_FROM_ISR(0);
}

void isr_rear1()
{
    //puts("inside isr3 \n");
    actual_time_rear = lpc_timer_get_value(lpc_timer0) - start_time_rear;
    obstacle.rear_distance = actual_time_rear / 147;
    portYIELD_FROM_ISR(0);
}

void isr_middle()
{
    //puts("inside isr1");
    start_time_middle = lpc_timer_get_value(lpc_timer0);


}
void isr_right()
{
    //puts("inside isr1");
    start_time_right = lpc_timer_get_value(lpc_timer0);

}
void isr_left()
{
    //puts("inside isr1");
    start_time_left = lpc_timer_get_value(lpc_timer0);

}
void isr_rear()
{
    //puts("inside isr1");
    start_time_rear = lpc_timer_get_value(lpc_timer0);

}


void sensor_sonar_middle_trigger()
{
    LPC_GPIO1->FIODIR |= (1 << 23);
    LPC_GPIO1->FIOPIN &= ~(1 << 23);
    LPC_GPIO1->FIOPIN |= (1 << 23);
    delay_us(SENSOR_DELAY);
    LPC_GPIO1->FIOPIN &= ~(1 << 23);

}

void sensor_sonar_right_trigger()
{
    LPC_GPIO1->FIODIR |= (1 << 22);
    LPC_GPIO1->FIOPIN &= ~(1 << 22);
    LPC_GPIO1->FIOPIN |= (1 << 22);
    delay_us(SENSOR_DELAY);
    LPC_GPIO1->FIOPIN &= ~(1 << 22);
}

void sensor_sonar_left_trigger()
{
    LPC_GPIO1->FIODIR |= (1 << 28);
    LPC_GPIO1->FIOPIN &= ~(1 << 28);
    LPC_GPIO1->FIOPIN |= (1 << 28);
    delay_us(SENSOR_DELAY);
    LPC_GPIO1->FIOPIN &= ~(1 << 28);
}

void sensor_sonar_rear_trigger()
{LPC_GPIO1->FIODIR |= (1 << 29);
LPC_GPIO1->FIOPIN &= ~(1 << 29);
LPC_GPIO1->FIOPIN |= (1 << 29);
delay_us(SENSOR_DELAY);
LPC_GPIO1->FIOPIN &= ~(1 << 29);
}

void interrupt_enable()
{
    eint3_enable_port2(1,eint_rising_edge,isr_right);
    eint3_enable_port2(3,eint_rising_edge,isr_middle);
    eint3_enable_port2(5,eint_rising_edge,isr_left);
    eint3_enable_port2(7,eint_rising_edge,isr_rear);

}
void interrupt_falling_edge_enable()
{
    eint3_enable_port2(1,eint_falling_edge,isr_right1);
    eint3_enable_port2(3,eint_falling_edge,isr_middle1);
    eint3_enable_port2(5,eint_falling_edge,isr_left1);
    eint3_enable_port2(7,eint_falling_edge,isr_rear1);
}
void sensor_receiver_pins()
{
    /*LPC_GPIO2->FIODIR &= ~(1 << 1);
    LPC_GPIO2->FIODIR &= ~(1 << 3);
    LPC_GPIO2->FIODIR &= ~(1 << 5);
    LPC_GPIO2->FIODIR &= ~(1 << 7);*/
}

void can_init_sensor()
{
    CAN_init(can1, 100, 20, 20,0,0);
    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(can1);

    //return true;

}

void sensor_init(){

    /**
     * todo: CALVIN:remove this if it's not being used.
     * KARTHIK: will be removed after demo 2.
     */
    sensor_receiver_pins();

    interrupt_enable();
    lpc_timer_enable(lpc_timer0, TIMER_TICK);
    interrupt_falling_edge_enable();

}
void compute()
{
    uint8_t left,right,middle,rear;
    static uint8_t count,left_avg,right_avg,mid_avg,rear_avg,sum_left,sum_right,sum_mid,sum_rear,critical;
    static uint8_t left_old,middle_old,right_old,rear_old;
    static bool flag=false;
   // if(flag){
        left_old= sum_left;
        middle_old=sum_right;
        right_old= sum_mid;
        rear_old=sum_rear;
        sum_left= obstacle.left_distance;
        sum_right=obstacle.right_distance;
        sum_mid=obstacle.middle_distance;
        sum_rear=obstacle.rear_distance;
/*

        if(abs(sum_left-left_old)>30){
            sum_left=left_old;
        }
        if(abs(sum_right-right_old)>30){
            sum_right  =   right_old;
        }
        if(abs(sum_mid-middle_old)>30){
            sum_mid = middle_old;
        }
        if(abs(sum_rear-rear_old)>30){
            sum_rear  = rear_old;
        }

    }
    else{//get the first reading into the old variables
        left_old=obstacle.left_distance;
        middle_old = obstacle.right_distance;
        right_old=obstacle.right_distance;
        rear_old=obstacle.rear_distance;
        flag=true;
    }
*/




    if(sum_right<=30){
        right=1;
        LE.toggle(1);
    }
    else{
        right=0;
    }
    if(sum_mid<=45){
        middle=1;
        if(sum_mid<20){
            critical=1;
            LD.setNumber(88);
        }

        LE.toggle(2);
    }
    else{
        critical=0;
        middle=0;
    }
    /**
     * The preference for turn is left in case there is an obstacle in the
     * middle, so the sensitivity for the left side must be a little higher
     * than the right
     */
    if(sum_left<=38){
        left=1;
        LE.toggle(3);
    }
    else{
        left=0;
    }
    if(sum_rear<=45){
        rear=1;
        //LE.toggle(4);
    }
    else{
        rear=0;
    }
    // printf(" %d     %d      %d   %d\n",left_avg,right_avg,mid_avg,rear_avg);
    decoded_can_sensor_message(middle,left,right,left,critical);
}



void sensor_measure()
{
    sensor_sonar_middle_trigger();
    //sensor_sonar_rear_trigger();
    delay_ms(10);
    sensor_sonar_right_trigger();
    delay_ms(10);
    sensor_sonar_left_trigger();
    //delay_ms(10);
    // sensor_sonar_rear_trigger();
    compute();

}
void can_communication_sensor()
{
    static int counter_send = 0;
    counter_send++;
    // decoded_can_sensor_message();
    if(counter_send % 100==0)
        ultrasonic_sensor_heartbeat_message();

}

uint8_t received_sensor_can_msg()
{
    /**
     * todo: do not use while loops.
     */
    if(CAN_rx(can1, &can_msg_received, 0))
    {
        can_msg_hdr.dlc = can_msg_received.frame_fields.data_len;
        can_msg_hdr.mid = can_msg_received.msg_id;

        if(dbc_decode_MASTER_SYSTEM_CMD(&master_command, can_msg_received.data.bytes, &can_msg_hdr)){

        }

    }

    if(dbc_handle_mia_MASTER_SYSTEM_CMD(&master_command, 10))
    {

        counter++;

        if(counter == 99 )
            counter =0;

    }
    if(master_command.MASTER_SYSTEM_CMD_enum==SYSTEM_START){
        return 1;
    }
    else{
        return 0;
    }

}