/*
* File: lego_module.cpp
* Author: m79lol, iskinmike
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>
#include <vector>
#include <map>

#include "build_number.h"

#include "SimpleIni.h"

#include "module.h"
#include "robot_module.h"
#include "lego_ev3_robot_module.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

const unsigned int COUNT_LEGO_FUNCTIONS = 24;
const unsigned int COUNT_AXIS = 11;

#define IID "RCT.Lego_ev3_robot_module_v100"

#define ADD_LEGO_0_FUNCTION(FUNCTION_NAME)                       \
  lego_functions[function_id] =                                  \
      new FunctionData(function_id + 1, 0, NULL, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_1F_FUNCTION(FUNCTION_NAME)                        \
  Params = new FunctionData::ParamTypes[1];                        \
  Params[0] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 1, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_1S_FUNCTION(FUNCTION_NAME)                        \
  Params = new FunctionData::ParamTypes[1];                        \
  Params[0] = FunctionData::STRING;                                \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 1, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_2F_FUNCTION(FUNCTION_NAME)                        \
  Params = new FunctionData::ParamTypes[2];                        \
  Params[0] = FunctionData::FLOAT;                                 \
  Params[1] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 2, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_1S1F_FUNCTION(FUNCTION_NAME)                      \
  Params = new FunctionData::ParamTypes[2];                        \
  Params[0] = FunctionData::STRING;                                \
  Params[1] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 2, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_4F_FUNCTION(FUNCTION_NAME)                        \
  Params = new FunctionData::ParamTypes[4];                        \
  Params[0] = FunctionData::FLOAT;                                 \
  Params[1] = FunctionData::FLOAT;                                 \
  Params[2] = FunctionData::FLOAT;                                 \
  Params[3] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 4, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_1S3F_FUNCTION(FUNCTION_NAME)                      \
  Params = new FunctionData::ParamTypes[4];                        \
  Params[0] = FunctionData::STRING;                                \
  Params[1] = FunctionData::FLOAT;                                 \
  Params[2] = FunctionData::FLOAT;                                 \
  Params[3] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 4, Params, FUNCTION_NAME); \
  function_id++;
//////

#define ADD_LEGO_2S2F_FUNCTION(FUNCTION_NAME)                      \
  Params = new FunctionData::ParamTypes[4];                        \
  Params[0] = FunctionData::STRING;                                \
  Params[1] = FunctionData::STRING;                                \
  Params[2] = FunctionData::FLOAT;                                 \
  Params[3] = FunctionData::FLOAT;                                 \
  lego_functions[function_id] =                                    \
      new FunctionData(function_id + 1, 4, Params, FUNCTION_NAME); \
  function_id++;
//////

#define DEFINE_ALL_FUNCTIONS                           \
  ADD_LEGO_1S_FUNCTION("motorBrake")                   \
  ADD_LEGO_1S_FUNCTION("motorGetDirection")            \
  ADD_LEGO_1S_FUNCTION("motorGetTacho")                \
  ADD_LEGO_1S3F_FUNCTION("motorMoveTo")                \
  ADD_LEGO_1S_FUNCTION("motorOff")                     \
  ADD_LEGO_1S_FUNCTION("motorResetTacho")              \
  ADD_LEGO_1S1F_FUNCTION("motorSetDirection")          \
  ADD_LEGO_1S1F_FUNCTION("motorSetSpeed")              \
  ADD_LEGO_2S2F_FUNCTION("setTrackVehicle")            \
  ADD_LEGO_1S_FUNCTION("waitMotorToStop")              \
  ADD_LEGO_4F_FUNCTION("waitMultiMotorsToStop")        \
  ADD_LEGO_1F_FUNCTION("trackVehicleBackward")         \
  ADD_LEGO_1F_FUNCTION("trackVehicleForward")          \
  ADD_LEGO_0_FUNCTION("trackVehicleOff")               \
  ADD_LEGO_1F_FUNCTION("trackVehicleSpinLeft")         \
  ADD_LEGO_1F_FUNCTION("trackVehicleSpinRight")        \
  ADD_LEGO_2F_FUNCTION("trackVehicleTurnLeftForward")  \
  ADD_LEGO_2F_FUNCTION("trackVehicleTurnLeftReverse")  \
  ADD_LEGO_2F_FUNCTION("trackVehicleTurnRightForward") \
  ADD_LEGO_2F_FUNCTION("trackVehicleTurnRightForward") \
  ADD_LEGO_0_FUNCTION("trackVehicleBrake")             \
  ADD_LEGO_2F_FUNCTION("readSensor")                   \
  ADD_LEGO_1S1F_FUNCTION("isMotorRunning")             \
  ADD_LEGO_1S1F_FUNCTION("getMotorSpeed");

#define ADD_ROBOT_AXIS(AXIS_NAME, UPPER_VALUE, LOWER_VALUE) \
  \
robot_axis[axis_id] = new AxisData;                         \
  \
robot_axis[axis_id]->axis_index = axis_id + 1;              \
  \
robot_axis[axis_id]->upper_value = UPPER_VALUE;             \
  \
robot_axis[axis_id]->lower_value = LOWER_VALUE;             \
  \
robot_axis[axis_id]->name = AXIS_NAME;                      \
  \
axis_id++;

#define DEFINE_ALL_AXIS \
  \
ADD_ROBOT_AXIS("locked", 1, 0) \
ADD_ROBOT_AXIS("speedMotorA", 100, -100) \
ADD_ROBOT_AXIS("speedMotorB", 100, -100) \
ADD_ROBOT_AXIS("speedMotorC", 100, -100) \
ADD_ROBOT_AXIS("speedMotorD", 100, -100) \
ADD_ROBOT_AXIS("moveMotorA", 1000, -1000) \
ADD_ROBOT_AXIS("moveMotorB", 1000, -1000) \
ADD_ROBOT_AXIS("moveMotorC", 1000, -1000) \
ADD_ROBOT_AXIS("moveMotorD", 1000, -1000) \
ADD_ROBOT_AXIS("straight", 100, -100) \
ADD_ROBOT_AXIS("rotation", 100, -100);

const struct ModuleInfo &LegoRobotModule::getModuleInfo() { return *mi; }

FunctionData **LegoRobotModule::getFunctions(unsigned int *count_functions) {
  *count_functions = COUNT_LEGO_FUNCTIONS;
  return lego_functions;
};

LegoRobotModule::LegoRobotModule() {
  mi = new ModuleInfo;
  mi->uid = IID;
  mi->mode = ModuleInfo::Modes::PROD;
  mi->version = BUILD_NUMBER;
  mi->digest = NULL;

  srand(time(NULL));
  lego_functions = new FunctionData *[COUNT_LEGO_FUNCTIONS];
  system_value function_id = 0;
  FunctionData::ParamTypes *Params = NULL;

  // define robot functions
  DEFINE_ALL_FUNCTIONS

  // define robot axis
  robot_axis = new AxisData *[COUNT_AXIS];
  system_value axis_id = 0;
  DEFINE_ALL_AXIS
};

inline void isSpeed(variable_value num) {
  if ((num < (-100)) || (num > 100)) {
    throw std::exception();
  }
};

inline void isPercent(variable_value num) {
  if ((num < 0) || (num > 100)) {
    throw std::exception();
  }
};

inline void isMotor(wchar_t num) {
  switch (num) {
    case 'A':
    case 'B':
    case 'C':
    case 'D': {
      break;
    }
    default:
      throw std::exception();
  }
};

void LegoRobotModule::destroy() {
  delete mi;
  for (unsigned int j = 0; j < COUNT_LEGO_FUNCTIONS; ++j) {
    if (lego_functions[j]->count_params) {
      delete[] lego_functions[j]->params;
    }
    delete lego_functions[j];
  }
  for (unsigned int j = 0; j < COUNT_AXIS; ++j) {
    delete robot_axis[j];
  }
  delete[] lego_functions;
  delete[] robot_axis;
  delete this;
};
int LegoRobotModule::init() {
  InitializeCriticalSection(&LRM_cs);
  CSimpleIniA ini;
  ini.SetMultiKey(true);

  WCHAR DllPath[MAX_PATH] = {0};

  GetModuleFileNameW((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));

  WCHAR *tmp = wcsrchr(DllPath, L'\\');
  WCHAR ConfigPath[MAX_PATH] = {0};
  size_t path_len = tmp - DllPath;
  wcsncpy(ConfigPath, DllPath,
          path_len);  // VStudio Reccomends wcsncpy_s() instead
  wcscat(ConfigPath, L"\\config.ini");

  if (ini.LoadFile(ConfigPath) < 0) {
    colorPrintf(ConsoleColor(ConsoleColor::red), "Can't load '%s' file!\n",
                ConfigPath);
    return 1;
  }

  allow_dynamic = ini.GetBoolValue("options", "dynamic_connection", false);

  CSimpleIniA::TNamesDepend values;
  ini.GetAllValues("connections", "connection", values);
  CSimpleIniA::TNamesDepend::const_iterator ini_value;

  for (ini_value = values.begin(); ini_value != values.end(); ++ini_value) {
    colorPrintf(ConsoleColor(ConsoleColor::green), "- %s\n", ini_value->pItem);
    std::string connection(ini_value->pItem);
    LegoRobot *lego_robot = new LegoRobot(connection, allow_dynamic);
    aviable_connections[connection] = lego_robot;
  }
  return 0;
};

Robot *LegoRobotModule::robotRequire() {
  EnterCriticalSection(&LRM_cs);
  for (m_connections::iterator i = aviable_connections.begin();
       i != aviable_connections.end(); ++i) {
    if ((*i).second->require()) {
      LeaveCriticalSection(&LRM_cs);
      return (*i).second;
    }
  };
  LeaveCriticalSection(&LRM_cs);
  return NULL;
};

bool LegoRobot::require() {
  if (!is_aviable) {
    return false;
  }

  if (allow_dynamic) {
    if (!connect()) {
      return false;
    }
  }

  is_aviable = false;
  return true;
};

void LegoRobot::free() {
  if (is_aviable) {
    return;
  }
  is_aviable = true;

  if (allow_dynamic) {
    disconnect();
    Sleep(1000);
  }
};

bool LegoRobot::connect() {
  lego_communication_library::EV3_brick ^ singletoneBrick =
      lego_communication_library::EV3_brick::getInstance();
  try {
    singletoneBrick->connectBrick(robot_index);
    // colorPrintf(ConsoleColor(ConsoleColor::yellow),"Connected to %s robot\n",
    // connection.c_str());
  } catch (...) {
    singletoneBrick->disconnectBrick(robot_index);
    return false;
  }
  return true;
}

void LegoRobot::disconnect() {
  lego_communication_library::EV3_brick ^ singletoneBrick =
      lego_communication_library::EV3_brick::getInstance();
  singletoneBrick->disconnectBrick(robot_index);
}

void LegoRobotModule::robotFree(Robot *robot) {
  EnterCriticalSection(&LRM_cs);
  LegoRobot *lego_robot = reinterpret_cast<LegoRobot *>(robot);
  for (m_connections::iterator i = aviable_connections.begin();
       i != aviable_connections.end(); ++i) {
    if (i->second == lego_robot) {
      lego_robot->free();
      break;
    }
  }
  LeaveCriticalSection(&LRM_cs);
};
AxisData **LegoRobotModule::getAxis(unsigned int *count_axis) {
  (*count_axis) = COUNT_AXIS;
  return robot_axis;
};
void LegoRobotModule::final() {
  for (m_connections::iterator i = aviable_connections.begin();
       i != aviable_connections.end(); ++i) {
    if (!allow_dynamic) {
      i->second->disconnect();
    }
    delete i->second;
  }
  aviable_connections.clear();
};
void LegoRobot::axisControl(system_value axis_index, variable_value value) {
  switch (axis_index) {
    case 1: {
      is_locked = !!value;
      break;
    };
    case 2:
    case 3:
    case 4:
    case 5: {  // setSpeedMotor A.B.C.D
      if (!is_locked) {
        lego_communication_library::EV3_brick::getInstance()->motorSetSpeed(
            robot_index, (wchar_t)(63 + axis_index), (int)value);
      }
      break;
    };
    case 6:
    case 7:
    case 8:
    case 9: {  // moveMotor A,B,C,D
      if (!is_locked) {
        lego_communication_library::EV3_brick::getInstance()->motorMoveTo(
            robot_index, (wchar_t)(59 + axis_index), 50, (int)value, false);  //
      }
      break;
    };
    case 10: {
      if (!is_locked) {
        lego_communication_library::EV3_brick::getInstance()
            ->trackVehicleForward(robot_index, (int)value);
      }
      break;
    };
    case 11: {
      if (!is_locked) {
        lego_communication_library::EV3_brick::getInstance()
            ->trackVehicleSpinRight(robot_index, (int)value);
      }
      break;
    };
  };
};
void LegoRobotModule::prepare(colorPrintfModule_t *colorPrintf_p,
                              colorPrintfModuleVA_t *colorPrintfVA_p) {
  this->colorPrintf_p = colorPrintfVA_p;
}
void LegoRobot::prepare(colorPrintfRobot_t *colorPrintf_p,
                        colorPrintfRobotVA_t *colorPrintfVA_p) {
  this->colorPrintf_p = colorPrintfVA_p;
}

void *LegoRobotModule::writePC(unsigned int *buffer_length) {
  *buffer_length = 0;
  return NULL;
}

FunctionResult *LegoRobot::executeFunction(CommandMode mode,
                                           system_value functionId,
                                           void **args) {
  if ((functionId < 1) || (functionId > COUNT_LEGO_FUNCTIONS)) {
    return NULL;
  }
  FunctionResult *fr = NULL;

  try {
    variable_value rez = 0;
    switch (functionId) {
      case 1: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        lego_communication_library::EV3_brick::getInstance()->motorBrake(
            robot_index, input1);

        break;
      }
      case 2: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        rez = lego_communication_library::EV3_brick::getInstance()
                  ->motorGetDirection(robot_index, input1);
        break;
      }
      case 3: {
        wchar_t input1 = *(const char *)args[0];

        isMotor(input1);
        rez =
            lego_communication_library::EV3_brick::getInstance()->motorGetTacho(
                robot_index, input1);
        break;
      }
      case 4: {
        wchar_t input1 = *(const char *)args[0];
        variable_value *input2 = (variable_value *)args[1];

        isSpeed(*input2);
        isMotor(input1);
        variable_value *input3 = (variable_value *)args[2];
        variable_value *input4 = (variable_value *)args[3];
        lego_communication_library::EV3_brick::getInstance()->motorMoveTo(
            robot_index, input1, *input2, *input3, !!(*input4));
        break;
      }
      case 5: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        lego_communication_library::EV3_brick::getInstance()->motorOff(
            robot_index, input1);

        break;
      }
      case 6: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        lego_communication_library::EV3_brick::getInstance()->motorResetTacho(
            robot_index, input1);
        break;
      }
      case 7: {
        wchar_t input1 = *(const char *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isMotor(input1);
        lego_communication_library::EV3_brick::getInstance()->motorSetDirection(
            robot_index, input1, !!(*input2));
        break;
      }
      case 8: {
        wchar_t input1 = *(const char *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isMotor(input1);
        isSpeed(*input2);
        lego_communication_library::EV3_brick::getInstance()->motorSetSpeed(
            robot_index, input1, *input2);
        break;
      }
      case 9: {
        wchar_t input1 = *(const char *)args[0];
        wchar_t input2 = *(const char *)args[1];

        isMotor(input1);
        isMotor(input2);
        variable_value *input3 = (variable_value *)args[2];
        variable_value *input4 = (variable_value *)args[3];
        if (input1 != input2) {
          lego_communication_library::EV3_brick::getInstance()->setTrackVehicle(
              robot_index, input1, input2, (bool)(*input3), (bool)(*input4));
          is_trackVehicleOn = true;
        } else {
          throw std::exception();
        };
        break;
      }
      case 10: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        lego_communication_library::EV3_brick::getInstance()->waitMotorToStop(
            robot_index, input1);
        break;
      }
      case 11: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        variable_value *input3 = (variable_value *)args[2];
        variable_value *input4 = (variable_value *)args[3];
        lego_communication_library::EV3_brick::getInstance()
            ->waitMultiMotorsToStop(robot_index, !!(*input1), !!(*input2),
                                    !!(*input3), !!(*input4));
        break;
      }
      case 12: {
        variable_value *input1 = (variable_value *)args[0];
        isSpeed(*input1);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleBackward(robot_index, *input1);
        } else {
          throw std::exception();
        };
        break;
      }
      case 13: {
        variable_value *input1 = (variable_value *)args[0];
        isSpeed(*input1);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleForward(robot_index, *input1);
        } else {
          throw std::exception();
        };
        break;
      }
      case 14: {
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()->trackVehicleOff(
              robot_index);
        } else {
          throw std::exception();
        };
        break;
      }
      case 15: {
        variable_value *input1 = (variable_value *)args[0];
        isSpeed(*input1);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleSpinLeft(robot_index, *input1);
        } else {
          throw std::exception();
        };
        break;
      }
      case 16: {
        variable_value *input1 = (variable_value *)args[0];
        isSpeed(*input1);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleSpinRight(robot_index, *input1);
        } else {
          throw std::exception();
        };
        break;
      }
      case 17: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isSpeed(*input1);
        isPercent(*input2);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleTurnLeftForward(robot_index, *input1, *input2);
        } else {
          throw std::exception();
        };
        break;
      }
      case 18: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isPercent(*input2);
        isSpeed(*input1);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleTurnLeftReverse(robot_index, *input1, *input2);
        } else {
          throw std::exception();
        };
        break;
      }
      case 19: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isSpeed(*input1);
        isPercent(*input2);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleTurnRightForward(robot_index, *input1, *input2);
        } else {
          throw std::exception();
        };
        break;
      }
      case 20: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        isSpeed(*input1);
        isPercent(*input2);
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleTurnRightForward(robot_index, *input1, *input2);
        } else {
          throw std::exception();
        };
        break;
      }
      case 21: {
        if (is_trackVehicleOn) {
          lego_communication_library::EV3_brick::getInstance()
              ->trackVehicleBrake(robot_index);
        } else {
          throw std::exception();
        };
        break;
      }
      case 22: {
        variable_value *input1 = (variable_value *)args[0];
        variable_value *input2 = (variable_value *)args[1];
        if (lego_communication_library::EV3_brick::getInstance()
                ->testSensorMode(robot_index, *input1, *input2)) {
          rez =
              lego_communication_library::EV3_brick::getInstance()->readSensor(
                  robot_index, *input1, *input2);
        } else {
          throw std::exception();
        };
        break;
      }
      case 23: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        variable_value *input2 = (variable_value *)args[1];
        rez = lego_communication_library::EV3_brick::getInstance()
                  ->isMotorRunning(robot_index, input1, !!(*input2));
        break;
      }
      case 24: {
        wchar_t input1 = *(const char *)args[0];
        isMotor(input1);
        variable_value *input2 = (variable_value *)args[1];
        rez =
            lego_communication_library::EV3_brick::getInstance()->getMotorSpeed(
                robot_index, input1, !!(*input2));
        break;
      }
    };
    fr = new FunctionResult(FunctionResult::Types::VALUE, rez); 
  } catch (...) {
    fr = new FunctionResult(FunctionResult::Types::EXCEPTION);
  };
  return fr;
};

int LegoRobotModule::startProgram(int uniq_index) { return 0; }

void LegoRobotModule::readPC(void *buffer, unsigned int buffer_length) {}

int LegoRobotModule::endProgram(int uniq_index) { return 0; }

LegoRobot::LegoRobot(std::string connection, bool allow_dynamic)
    : connection(connection),
      is_aviable(true),
      is_trackVehicleOn(false),
      is_locked(false),
      allow_dynamic(allow_dynamic) {
  System::String ^ connection_c = gcnew System::String(connection.c_str());
  lego_communication_library::EV3_brick ^ singletoneBrick =
      lego_communication_library::EV3_brick::getInstance();
  robot_index = singletoneBrick->createBrick(connection_c);

  uniq_name = new char[40];
  sprintf(uniq_name, "robot-%s", connection.c_str());

  if (!allow_dynamic) {
    if (!connect()) {
      is_aviable = false;
    }
  }
}

LegoRobot::~LegoRobot() { delete[] uniq_name; }

void LegoRobotModule::colorPrintf(ConsoleColor colors, const char *mask, ...) {
  va_list args;
  va_start(args, mask);
  (*colorPrintf_p)(this, colors, mask, args);
  va_end(args);
}

void LegoRobot::colorPrintf(ConsoleColor colors, const char *mask, ...) {
  va_list args;
  va_start(args, mask);
  (*colorPrintf_p)(this, uniq_name, colors, mask, args);
  va_end(args);
}

PREFIX_FUNC_DLL unsigned short getRobotModuleApiVersion() {
  return MODULE_API_VERSION;
};

__declspec(dllexport) RobotModule *getRobotModuleObject() {
  return new LegoRobotModule();
};