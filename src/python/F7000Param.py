#!/usr/bin/python
# -*- coding: UTF-8 -*-

import xml.etree.cElementTree as ET
import time
from table import Table

class F7000Xml():
  def __init__(self):
    self.root_ = None

  def toBool(self, value):
    return True if value == "true" else False

  def Parse(self, path):
    self.before_load_time_ = time.time()
    tree = ET.parse(path)
    self.root_ = tree.getroot()

  def GetAttr(self, node, attr, type):
    if (self.root_):
      for e in self.root_.iter(node):
        if type == 'bool':
          return self.toBool(e.get(attr))
        elif type == 'int':
          return int(e.get(attr))
        elif type == 'float':
          return float(e.get(attr))
        elif type == 'string':
          return e.get(attr)


class In():
  # Input index and size information
  x_limit_p = 1
  x_limit_n = 2
  y_limit_p = 3
  y_limit_n = 4
  emg = 5
  arc_feedback = 6
  position_feedback = 7
  crash_check = 14
  forward_motion = 8
  back_motion = 9
  left_motion = 10
  right_motion = 11
  up_input = 12
  down_input = 13
  torch_up = 15
  torch_down = 0
  input_size = 16

  def __init__(self, f7000xml):
    self.input_noes_ = [True] * In.input_size
    for input in f7000xml.root_.iter("Input"):
      self.input_noes_[int(input.get("InputNum"))] = f7000xml.toBool(input.get("InputNC"))

  def XLimitP(self):
    return In.x_limit_p

  def XLimitN(self):
    return In.x_limit_n

  def YLimitP(self):
    return In.y_limit_p

  def YLimitN(self):
    return In.y_limit_n

  def Emg(self):
    return In.emg

  def ArcFeedback(self):
    return In.arc_feedback

  def PositionFeedBack(self):
    return In.position_feedback

  def CrashCheck(self):
    return In.crash_check

  def FowardMotion(self):
    return In.forward_motion

  def BackMotion(self):
    return In.back_motion

  def LeftMotion(self):
    return In.left_motion

  def RightMotion(self):
    return In.right_motion

  def UpInput(self):
    return In.up_input

  def DownInput(self):
    return In.down_input

  def TorchUp(self):
    return In.torch_up

  def TotchDown(self):
    return In.torch_down

  # Normal open input
  def XLimitPIsNO(self):
    return not self.input_noes_[In.x_limit_p]

  def XLimitNIsNO(self):
    return not self.input_noes_[In.x_limit_n]

  def YLimitPIsNO(self):
    return not self.input_noes_[In.y_limit_p]

  def YLimitNIsNO(self):
    return not self.input_noes_[In.y_limit_n]

  def EmgIsNO(self):
    return not self.input_noes_[In.emg]

  def ArcFeedbackIsNO(self):
    return not self.input_noes_[In.arc_feedback]

  def PositionFeedBackIsNO(self):
    return not self.input_noes_[In.position_feedback]

  def CrashCheckIsNO(self):
    return not self.input_noes_[In.crash_check]

  def FowardMotionIsNO(self):
    return not self.input_noes_[In.forward_motion]

  def BackMotionIsNO(self):
    return not self.input_noes_[In.back_motion]

  def LeftMotionIsNO(self):
    return not self.input_noes_[In.left_motion]

  def RightMotionIsNO(self):
    return not self.input_noes_[In.right_motion]

  def UpInputIsNO(self):
    return not self.input_noes_[In.up_input]

  def DownInputIsNO(self):
    return not self.input_noes_[In.down_input]

  def TorchUpIsNO(self):
    return not self.input_noes_[In.torch_up]

  def TotchDownIsNO(self):
    return not self.input_noes_[In.torch_down]

class Out():
  # Output index and size information
  fire_switch = 0
  low_preheat = 2
  high_preheat = 3
  low_cut = 4
  middle_cut = 5
  high_cut = 6
  torch_rise = 7
  torch_down = 14
  exhaust_port = 8
  enable_thc = 9
  plasma_position = 10
  plasma_arc = 11
  close_thc = 12
  spraying = 13
  powder = 15
  spraying_preheating = 1
  output_size = 16

  def __init__(self, f7000xml):
    self.output_ncs_ = [True] * Out.output_size
    for output in f7000xml.root_.iter("Output"):
      self.output_ncs_[int(output.get("OutputNum"))] = f7000xml.toBool(output.get("OutputNC"))

  def FireSwitch(self):
    return Out.fire_switch

  def LowPreheat(self):
    return Out.low_preheat

  def HighPreheat(self):
    return Out.high_preheat

  def LowCut(self):
    return Out.low_cut

  def MiddleCut(self):
    return Out.middle_cut

  def HighCut(self):
    return Out.high_cut

  def TorchRise(self):
    return Out.torch_rise

  def TorchDown(self):
    return Out.torch_down

  def ExhaustPort(self):
    return Out.exhaust_port

  def EnableThc(self):
    return Out.enable_thc

  def PlasmaPosition(self):
    return Out.plasma_position

  def PlasmaArc(self):
    return Out.plasma_arc

  def CloseThc(self):
    return Out.close_thc

  def Spraying(self):
    return Out.spraying

  def Powder(self):
    return Out.powder

  def SprayingPreheating(self):
    return Out.spraying_preheating

  def Creep(self):
    return 1000

  # Normal open output
  def FireSwitchIsNO(self):
    return not self.output_ncs_[Out.fire_switch]

  def LowPreheatIsNO(self):
    return not self.output_ncs_[Out.low_preheat]

  def HighPreheatIsNO(self):
    return not self.output_ncs_[Out.high_preheat]

  def LowCutIsNO(self):
    return not self.output_ncs_[Out.low_cut]

  def MiddleCutIsNO(self):
    return not self.output_ncs_[Out.middle_cut]

  def HighCutIsNO(self):
    return not self.output_ncs_[Out.high_cut]

  def TorchRiseIsNO(self):
    return not self.output_ncs_[Out.torch_rise]

  def TorchDownIsNO(self):
    return not self.output_ncs_[Out.torch_down]

  def ExhaustPortIsNO(self):
    return not self.output_ncs_[Out.exhaust_port]

  def EnableThcIsNO(self):
    return not self.output_ncs_[Out.enable_thc]

  def PlasmaPositionIsNO(self):
    return not self.output_ncs_[Out.plasma_position]

  def PlasmaArcIsNO(self):
    return not self.output_ncs_[Out.plasma_arc]

  def CloseThcIsNO(self):
    return not self.output_ncs_[Out.close_thc]

  def SprayingIsNO(self):
    return not self.output_ncs_[Out.spraying]

  def PowderIsNO(self):
    return not self.output_ncs_[Out.powder]

  def SprayingPreheatingIsNO(self):
    return not self.output_ncs_[Out.spraying_preheating]

class F7000Param():
  def ParseInOut(self, f7000xml):
    self.out_ = Out(f7000xml)
    self.in_ = In(f7000xml)

  def Parse(self, table):
    f7000xml_ = F7000Xml()
    f7000xml_.Parse("/tmp/f7000param.xml")
    self.ParseInOut(f7000xml_)
    #all
    self.edge_perforated_ = f7000xml_.GetAttr("SystemArgs", "EdgePierce", 'bool')
    self.use_thc_ = f7000xml_.GetAttr("SystemArgs", "THCEnable", 'bool')
    # oxygen
    self.keep_preheat_oxygen_ = f7000xml_.GetAttr("PLCConfig", "PreheatKeeping", 'bool')
    self.oxygen_creep_time_ = f7000xml_.GetAttr("Creep", "OxygenCreepTime", 'float')
    self.oxygen_creep_speed_ = f7000xml_.GetAttr("Creep", "OxygenCreepSpeed", 'float')
    self.ignition_time_ = f7000xml_.GetAttr("ProcessTime", "IgniteTime", 'float')
    self.torch_down_time_ = f7000xml_.GetAttr("ProcessTime", "TorchDownTime", 'float')
    self.high_preheat_time_ = f7000xml_.GetAttr("ProcessTime", "HighPreheatTime", 'float')
    self.low_preheat_time_ = f7000xml_.GetAttr("ProcessTime", "LowPreheatTime", 'float')
    self.pierce_up_time_ = f7000xml_.GetAttr("Pierce", "PierceTorchUpTime", 'float')
    self.pierce_1_time_ = f7000xml_.GetAttr("Pierce", "Pierce1Time", 'float')
    self.pierce_2_time_ = f7000xml_.GetAttr("Pierce", "Pierce2Time", 'float')
    self.pierce_3_time_ = f7000xml_.GetAttr("Pierce", "Pierce3Time", 'float')
    self.pierce_down_time_ = f7000xml_.GetAttr("Pierce", "PierceTorchDownTime", 'float')
    self.oxygen_torch_up_time_ = f7000xml_.GetAttr("ProcessTime", "OxygenTorchUpTime", 'float')
    self.exhaust_time_ = f7000xml_.GetAttr("ProcessTime", "BlowTime", 'float')
    # plasma
    self.arc_voltage_check_ = f7000xml_.GetAttr("ArcVoltageSetting", "ArcVoltageCheck", 'bool')
    self.use_cylinder_thc_ = f7000xml_.GetAttr("THC", "CylinderTHCEnable", 'bool')
    self.low_speed_close_THC_ratio_ = f7000xml_.GetAttr("THC", "LSpeedTHCOffRatio", 'float')
    self.close_thc_min_distance_ = f7000xml_.GetAttr("THC", "THCOffMinDis", 'float')
    self.advance_close_arc_voltage_time_ = f7000xml_.GetAttr("ArcVoltageSetting", "TimeAheadOfVoltageOff", 'float')
    self.break_arc_check_time_ = f7000xml_.GetAttr("ArcAndLocate", "ArcBreakingCheckTime", 'float')
    self.plasma_creep_time_ = f7000xml_.GetAttr("Creep", "PlasmaCreepTime", 'float')
    self.plasma_creep_speed_ = f7000xml_.GetAttr("Creep", "PlasmaCreepSpeed", 'float')
    self.plasma_perforated_thc_delay_time_ = f7000xml_.GetAttr("Pierce", "ThcDelayAfterPlasmaPierce", 'float')
    self.plasma_perforated_rising_time_ = f7000xml_.GetAttr("Pierce", "PlasmaPierceTorchUpTime", 'float')
    self.plasma_perforated_decline_time_ = f7000xml_.GetAttr("Pierce", "PlasmaPierceTorchDownTime", 'float')
    self.positioning_check_time_ = f7000xml_.GetAttr("ArcAndLocate", "LocateCheckTime", 'float')
    self.positioning_rising_time_ = f7000xml_.GetAttr("ArcAndLocate", "LocateTorchUpTime", 'float')
    self.arc_delay_time_ = f7000xml_.GetAttr("ArcAndLocate", "ArcingDelay", 'float')
    self.arc_check_time_ = f7000xml_.GetAttr("ArcAndLocate", "ArcingCheckTime", 'float')
    self.preforate_time_ = f7000xml_.GetAttr("Pierce", "PierceTime", 'float')
    self.plasma_torch_up_time_ = f7000xml_.GetAttr("ProcessTime", "PlasmaTorchUpTime", 'float')
    # powder and spray
    self.spraying_fire_time_ = f7000xml_.GetAttr("PowderAndSpraying", "SprayingIgniteTime", 'float')
    self.spraying_falling_time_ = f7000xml_.GetAttr("PowderAndSpraying", "SprayingDownTime", 'float')
    self.spraying_preheating_time_ = f7000xml_.GetAttr("PowderAndSpraying", "SprayingPreheatTime", 'float')
    self.powder_open_time_ = f7000xml_.GetAttr("PowderAndSpraying", "PowderOnTime", 'float')
    self.powder_close_time_ = f7000xml_.GetAttr("PowderAndSpraying", "PowderOffTime", 'float')
    self.spraying_rising_time_ = f7000xml_.GetAttr("PowderAndSpraying", "SprayingUpTime", 'float')
    self.spraying_offset_x_ = f7000xml_.GetAttr("TorchOffset", "SprayingHOffset", 'float')
    self.spraying_offset_y_ = f7000xml_.GetAttr("TorchOffset", "SprayingVOffset", 'float')
    self.plasma_offset_x_ = f7000xml_.GetAttr("TorchOffset", "PlasmaHOffetByFlame", 'float')
    self.plasma_offset_y_ = f7000xml_.GetAttr("TorchOffset", "PlasmaVOffetByFlame", 'float')

    self.display_table_ = {}
    self.times_ = {}

    name = "ignition_time"
    self.times_[name] = self.ignition_time_
    self.display_table_[name] = table.FIRE_DISPLAY_TIME

    name = "torch_down_time"
    self.times_[name] = self.torch_down_time_
    self.display_table_[name] = table.TORCH_DOWN_TIME

    name = "high_preheat_time"
    self.times_[name] = self.high_preheat_time_
    self.display_table_[name] = table.HIGH_PREHEAT_TIME

    name = "low_preheat_time"
    self.times_[name] = self.low_preheat_time_
    self.display_table_[name] = table.LOW_PREHEAT_TIME

    name = "pierce_up_time"
    self.times_[name] = self.pierce_up_time_ #{{OneCute_value.ini/OneCut/PerforateRisingTime\perforated_rising_time}}
    self.display_table_[name] = table.TORCH_UP_TIME

    name = "pierce_1_time"
    self.times_[name] = self.pierce_1_time_#{{OneCute_value.ini/OneCut/PerforateTime1\level1_perforate_time}}
    self.display_table_[name] = table.PIERCE1_DISPLAY_TIME

    name = "pierce_2_time"
    self.times_[name] = self.pierce_2_time_#{{OneCute_value.ini/OneCut/PerforateTime2\level2_perforate_time}}
    self.display_table_[name] = table.PIERCE2_DISPLAY_TIME

    name = "pierce_3_time"
    self.times_[name] = self.pierce_3_time_#{{OneCute_value.ini/OneCut/PerforateTime3\level3_perforate_time}}
    self.display_table_[name] = table.PIERCE3_DISPLAY_TIME

    name = "pierce_down_time"
    self.times_[name] = self.pierce_down_time_#{{OneCute_value.ini/OneCut/PerforatedDeclineTime\perforated_decline_time}}
    self.display_table_[name] = table.TORCH_DOWN_TIME

    name = "spraying_fire_time"
    self.times_[name] = self.spraying_fire_time_#{{OneCute_value.ini/OneCut/SprayingFireTime\spraying_fire_time}}
    self.display_table_[name] = table.SPRAYING_FIRE_TIME

    name = "spraying_falling_time"
    self.times_[name] = self.spraying_falling_time_#{{OneCute_value.ini/OneCut/SprayingFallingTime\spraying_falling_time}}
    self.display_table_[name] = table.SPRAYING_FALLING_TIME

    name = "spraying_preheating_time"
    self.times_[name] = self.spraying_preheating_time_#{{OneCute_value.ini/OneCut/SprayingPreheatTime\spraying_preheating_time}}
    self.display_table_[name] = table.SPRAYING_PREHEATING_TIME

    name = "powder_open_time"
    self.times_[name] = self.powder_open_time_#{{OneCute_value.ini/OneCut/PowderOpenTime\powder_open_time}}
    self.display_table_[name] = table.POWDER_OPEN_TIME

    name = "powder_close_time"
    self.times_[name] = self.powder_close_time_#{{OneCute_value.ini/OneCut/PowderCloseTime\powder_close_time}}
    self.display_table_[name] = table.POWDER_CLOSE_TIME

    name = "spraying_rising_time"
    self.times_[name] = self.spraying_rising_time_#{{OneCute_value.ini/OneCut/SprayingRisingTime\spraying_rising_time}}
    self.display_table_[name] = table.SPRAYING_RISING_TIME

    name = "oxygen_creep_time"
    self.times_[name] = self.oxygen_creep_time_#{{OneCute_value.ini/OneCut/CreepTime\oxygen_creep_time}}
    self.display_table_[name] = table.OXYGEN_CREEP_TIME

    name = "plasma_creep_time"
    self.times_[name] = self.plasma_creep_time_#{{OneCute_value.ini/OneCut/CreepTime\plasma_creep_time}}
    self.display_table_[name] = table.PLASMA_CREEP_TIME

    name = "plasma_perforated_rising_time"
    self.times_[name] = self.plasma_perforated_rising_time_#{{OneCute_value.ini/OneCut/PlasmaPerforatedRisingTime\plasma_perforated_rising_time}}
    self.display_table_[name] = table.TORCH_UP_TIME

    name = "plasma_perforated_decline_time"
    self.times_[name] = self.plasma_perforated_decline_time_#{{OneCute_value.ini/OneCut/PlasmaPerforatedDeclineTime\plasma_perforated_decline_time}}
    self.display_table_[name] = table.TORCH_DOWN_TIME

    name = "positioning_check_time"
    self.times_[name] = self.positioning_check_time_#{{OneCute_value.ini/OneCut/PosCheckTime\positioning_check_time}}
    self.display_table_[name] = table.POSITION_CHECK_TIME

    name = "positioning_rising_time"
    self.times_[name] = self.positioning_rising_time_#{{OneCute_value.ini/OneCut/PosRisingTime\positioning_rising_time}}
    self.display_table_[name] = table.TORCH_UP_TIME

    name = "arc_delay_time"
    self.times_[name] = self.arc_delay_time_#{{OneCute_value.ini/OneCut/DelayTime\arc_delay_time}}
    self.display_table_[name] = table.ARC_DELAY_TIME

    name = "arc_check_time"
    self.times_[name] = self.arc_check_time_#{{OneCute_value.ini/OneCut/CheckTime\arc_check_time}}
    self.display_table_[name] = table.ARC_CHECK_TIME

    name = "preforate_time"
    self.times_[name] = self.preforate_time_#{{OneCute_value.ini/OneCut/PerforateTime\preforate_time}}
    self.display_table_[name] = table.PERFORATED_DISPLAY_TIME

    name = "oxygen_torch_up_time"
    self.times_[name] = self.oxygen_torch_up_time_
    self.display_table_[name] = table.TORCH_UP_TIME

    name = "exhaust_time"
    self.times_[name] = self.exhaust_time_
    self.display_table_[name] = table.EXHAUST_DISPLAY_TIME

    name = "plasma_torch_up_time"
    self.times_[name] = self.plasma_torch_up_time_
    self.display_table_[name] = table.TORCH_UP_TIME

  def GetDisplayTable(self, name):
    if (self.display_table_.has_key(name)):
      return self.display_table_[name]
    else:
      return -1

  def GetTime(self, name):
    if (self.times_.has_key(name)):
      return self.times_[name]
    else:
      return 0.01

if __name__ == '__main__':
  from table import Table
  table_ = Table()
  config_param_ = F7000Param()
  config_param_.Parse(table_)
