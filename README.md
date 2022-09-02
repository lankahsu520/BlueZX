# 1. Overview
BlueZX is based on [BlueZ](http://www.bluez.org/) (bluez-5.56).

It wrapped all features of bluetoothctl and provides some callback functions.

You can create a noninteractive daemon easily.

# 2. Depend on

- [utilx9](https://github.com/lankahsu520/utilx9)
- [BlueZ](http://www.bluez.org)

# 3. Current Status



# 4. Build
   ```
$ make
   ```

# 5. Example or Usage
- bluetoothctl_clone - it is the same as bluetoothctl.

- bluezx_123 - a daemon.

```bash
$ ./bluezx_123 -d3
```

```c
#define UUID16_LANKAHSU520_SERVICE_F999           0xF999
#define UUID16_LANKAHSU520_CHRC_F900              0xF900
#define UUID16_LANKAHSU520_CHRC_F901              0xF901

```

# 6. License
BlueZX is based on [BlueZ](http://www.bluez.org/).


# 7. Documentation
Run an example and read it.

## 7.1. TestCase A

```mermaid
sequenceDiagram
	participant Phone
	participant bluezx_123

	Phone->>bluezx_123: WRITE Characteristic-0xF900 data: .. .. .. ...
	bluezx_123->>bluezx_123: simple_gatt_chrc_write_value_cb, set chrc->value as 1000
	
	Phone->>bluezx_123: READ Characteristic-0xF900 data: .. .. 
	bluezx_123->>Phone: return chrc->value (1000=0xF901)

```

## 7.2. TestCase B

```mermaid
flowchart LR
	dbusx_456 <--> |D-Bus / com.github.lankahsu520| bluezx_123

```

```bash
export BLUEZX_COMMAND="scan&on"
export BLUEZX_COMMAND="scan&off"
export BLUEZX_COMMAND="advertise.name&on"
export BLUEZX_COMMAND="advertise.timeout&120"
export BLUEZX_COMMAND="advertise&on"

export BLUEZX_COMMAND="pair&90:E8:68:85:9A:0A"
export BLUEZX_COMMAND="connect&90:E8:68:85:9A:0A"
export BLUEZX_COMMAND="disconnect&90:E8:68:85:9A:0A"

export BLUEZX_COMMAND="gatt.list-attributes&90:E8:68:85:9A:0A"
export BLUEZX_COMMAND="gatt.select-attribute&0000F999-0000-1000-8000-00805f9b34fb"
export BLUEZX_COMMAND="gatt.select-attribute&0000F900-0000-1000-8000-00805f9b34fb"
export BLUEZX_COMMAND="gatt.select-attribute&0000F901-0000-1000-8000-00805f9b34fb"

export BLUEZX_COMMAND="gatt.write&0xFF 0xFE 0x7B 0x22 0x75 0x73 0x65 0x72 0x22 0x3A 0x22 0x6C 0x61 0x6E 0x6B 0x61 0x22 0x7D 0xFF 0xFF"
export BLUEZX_COMMAND="gatt.write&0xFF 0xFE 0xFF 0xFF"
export BLUEZX_COMMAND="gatt.write&0x1C 0x56"
export BLUEZX_COMMAND="gatt.push&/work/codebase/testing.json"
export BLUEZX_COMMAND="gatt.stop"

export BLUEZX_COMMAND="debug"

./dbusx_456 -e "$BLUEZX_COMMAND"
```

## 7.3. TestCase C

```mermaid
sequenceDiagram
	participant dbusx_456 as dbusx_456 (pic1)
	participant bluezx_123a as bluezx_123 (pic1)
	participant bluezx_123b as bluezx_123 (pic2)

	dbusx_456-->>bluezx_123a:PUSH a file
  loop PUSH a file
	bluezx_123a->>bluezx_123b: WRITE Characteristic-0xF900 data: .. .. .. ...
  end
	
```

```bash
export BLUEZX_COMMAND="gatt.select-attribute&0000F900-0000-1000-8000-00805f9b34fb"
export BLUEZX_COMMAND="gatt.push&/work/codebase/testing.json"
export BLUEZX_COMMAND="gatt.stop"
export BLUEZX_COMMAND="debug"

./dbusx_456 -e "$BLUEZX_COMMAND"
```

# Appendix

# I. BlueZX

## I.1. bluetoothctl_clone

### II.1.1. Usage

```bash
Commands:
        repeater        Repeater
        debug           Set Debug Level 0~4
        list            List available controllers
        show            Controller information
        select          Select default controller
        devices         List available devices
        paired-devices  List paired devices
        system-alias    Set controller alias
        reset-alias     Reset controller alias
        power           Set controller power
        pairable        Set controller pairable mode
        discoverable    Set controller discoverable mode
        discoverable-timeout    Set discoverable timeout
        agent           Enable/disable agent with given capability
        default-agent   Set agent as the default one
        advertise       Enable/disable advertising with given type
        set-alias       Set device alias
        scan            Scan for devices
        info            Device information
        pair            Pair with device
        cancel-pairing  Cancel pairing with device
        trust           Trust device
        untrust         Untrust device
        block           Block device
        unblock         Unblock device
        remove          Remove device
        connect         Connect device
        disconnect      Disconnect device

        advertise.:
                uuids           Set/Get advertise uuids
                service         Set/Get advertise service data
                manufacturer    Set/Get advertise manufacturer data
                data            Set/Get advertise data
                discoverable    Set/Get advertise discoverable
                discoverable-timeout    Set/Get advertise discoverable timeout
                tx-power        Show/Enable/Disable TX power to be advertised
                name            Configure local name to be advertised
                appearance      Configure custom appearance to be advertised
                duration        Set/Get advertise duration
                timeout         Set/Get advertise timeout
                secondary       Set/Get advertise secondary channel
                clear           Clear advertise config

        monitor.:
                set-rssi-threshold      Set RSSI threshold parameter
                set-rssi-timeout        Set RSSI timeout parameter
                set-rssi-sampling-period        Set RSSI sampling period parameter
                add-or-pattern  Register 'or pattern' type monitor with the specified RSSI parameters
                get-pattern     Get advertisement monitor
                remove-pattern  Remove advertisement monitor
                get-supported-info      Get advertisement manager supported features and supported monitor types
                print-usage     Print the command usage

        scan.:
                uuids           Set/Get UUIDs filter
                rssi            Set/Get RSSI filter, and clears pathloss
                pathloss        Set/Get Pathloss filter, and clears RSSI
                transport       Set/Get transport filter
                duplicate-data  Set/Get duplicate data filter
                discoverable    Set/Get discoverable filter
                pattern         Set/Get pattern filter
                clear           Clears discovery filter.

        gatt.:
                read_chrc       Read characteristic value
                list-attributes List attributes
                select-attribute        Select attribute
                attribute-info  Select attribute
                read            Read attribute value
                write           Write attribute value
                push            Push a file
                stop            Stop pushing
                acquire-write   Acquire Write file descriptor
                release-write   Release Write file descriptor
                acquire-notify  Acquire Notify file descriptor
                release-notify  Release Notify file descriptor
                notify          Notify attribute value
                clone           Clone a device or attribute
                register-application    Register profile to connect
                unregister-application  Unregister profile
                register-service        Register application service.
                unregister-service      Unregister application service
                register-includes       Register as Included service in.
                unregister-includes     Unregister Included service.
                register-characteristic Register application characteristic
                unregister-characteristic       Unregister application characteristic
                register-descriptor     Register application descriptor
                unregister-descriptor   Unregister application descriptor

```

# II. [BlueZ](http://www.bluez.org/)

## II.1. [Main BlueZ tree - GitHub](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwihnYTJ7734AhXXAaYKHXNJAEUQFnoECAUQAQ&url=https%3A%2F%2Fgithub.com%2Fbluez%2Fbluez&usg=AOvVaw0MThZWOGRFpL3nnm3V_1Hc)
## II.2. bluetoothctl

### II.2.1. Usage

```bash
$ bluetoothctl --help
bluetoothctl ver 5.53
Usage:
        bluetoothctl [--options] [commands]
Options:
        --agent         Register agent handler: <capability>
        --monitor       Enable monitor output
        --timeout       Timeout in seconds for non-interactive mode
        --version       Display version
        --help          Display help
Commands:
        list            List available controllers
        show            Controller information
        select          Select default controller
        devices         List available devices
        paired-devices  List paired devices
        system-alias    Set controller alias
        reset-alias     Reset controller alias
        power           Set controller power
        pairable        Set controller pairable mode
        discoverable    Set controller discoverable mode
        discoverable-timeout    Set discoverable timeout
        agent           Enable/disable agent with given capability
        default-agent   Set agent as the default one
        advertise       Enable/disable advertising with given type
        set-alias       Set device alias
        scan            Scan for devices
        info            Device information
        pair            Pair with device
        trust           Trust device
        untrust         Untrust device
        block           Block device
        unblock         Unblock device
        remove          Remove device
        connect         Connect device
        disconnect      Disconnect device

        advertise.:
                uuids           Set/Get advertise uuids
                service         Set/Get advertise service data
                manufacturer    Set/Get advertise manufacturer data
                data            Set/Get advertise data
                discoverable    Set/Get advertise discoverable
                discoverable-timeout    Set/Get advertise discoverable timeout
                tx-power        Show/Enable/Disable TX power to be advertised
                name            Configure local name to be advertised
                appearance      Configure custom appearance to be advertised
                duration        Set/Get advertise duration
                timeout         Set/Get advertise timeout
                secondary       Set/Get advertise secondary channel
                clear           Clear advertise config

        scan.:
                uuids           Set/Get UUIDs filter
                rssi            Set/Get RSSI filter, and clears pathloss
                pathloss        Set/Get Pathloss filter, and clears RSSI
                transport       Set/Get transport filter
                duplicate-data  Set/Get duplicate data filter
                discoverable    Set/Get discoverable filter
                clear           Clears discovery filter.

        gatt.:
                list-attributes List attributes
                select-attribute        Select attribute
                attribute-info  Select attribute
                read            Read attribute value
                write           Write attribute value
                acquire-write   Acquire Write file descriptor
                release-write   Release Write file descriptor
                acquire-notify  Acquire Notify file descriptor
                release-notify  Release Notify file descriptor
                notify          Notify attribute value
                clone           Clone a device or attribute
                register-application    Register profile to connect
                unregister-application  Unregister profile
                register-service        Register application service.
                unregister-service      Unregister application service
                register-includes       Register as Included service in.
                unregister-includes     Unregister Included service.
                register-characteristic Register application characteristic
                unregister-characteristic       Unregister application characteristic
                register-descriptor     Register application descriptor
                unregister-descriptor   Unregister application descriptor

```

### II.2.2. Menu gatt

```bash
Menu gatt:
Available commands:
-------------------
list-attributes [dev/local]                       List attributes
select-attribute <attribute/UUID>                 Select attribute
attribute-info [attribute/UUID]                   Select attribute
read [offset]                                     Read attribute value
write <data=xx xx ...> [offset] [type]            Write attribute value
acquire-write                                     Acquire Write file descriptor
release-write                                     Release Write file descriptor
acquire-notify                                    Acquire Notify file descriptor
release-notify                                    Release Notify file descriptor
notify <on/off>                                   Notify attribute value
clone [dev/attribute/UUID]                        Clone a device or attribute
register-application [UUID ...]                   Register profile to connect
unregister-application                            Unregister profile
register-service <UUID> [handle]                  Register application service.
unregister-service <UUID/object>                  Unregister application service
register-includes <UUID> [handle]                 Register as Included service in.
unregister-includes <Service-UUID><Inc-UUID>      Unregister Included service.
register-characteristic <UUID> <Flags=read,write,notify...> [handle] Register application characteristic
unregister-characteristic <UUID/object>           Unregister application characteristic
register-descriptor <UUID> <Flags=read,write...> [handle] Register application descriptor
unregister-descriptor <UUID/object>               Unregister application descriptor
back                                              Return to main menu
version                                           Display version
quit                                              Quit program
exit                                              Quit program
help                                              Display help about this program
export                                            Print environment variables

```

## II.3. D-Bus Diagram

```mermaid
flowchart LR
	bluetoothctl <--> |D-Bus / ???| bluetoothd

```

```mermaid
sequenceDiagram
	participant bluetoothctl as bluetoothctl
	participant bluetoothd as bluetoothd

	bluetoothctl->>bluetoothd: 1. destination=org.freedesktop.DBus serial=1 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=Hello
	bluetoothd->>bluetoothctl: method return,<br>string ":1.268"

	bluetoothctl->>bluetoothd: 2. method call, destination=org.freedesktop.DBus serial=2 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.freedesktop.DBus',path='/org/freedesktop/DBus',interface='org.freedesktop.DBus',member='NameOwnerChanged',arg0='org.bluez'"
	bluetoothd->>bluetoothctl: method return, 

	bluetoothctl->>bluetoothd: 3. destination=org.freedesktop.DBus serial=3 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=GetNameOwner<br>string "org.bluez"
	bluetoothd->>bluetoothctl: method return,<br>string ":1.135"

	bluetoothctl->>bluetoothd: 4. destination=org.freedesktop.DBus serial=4 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesAdded'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 5. destination=org.freedesktop.DBus serial=5 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesRemoved'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 6. destination=org.freedesktop.DBus serial=6 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path_namespace='/org/bluez'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 7. destination=org.bluez serial=7 path=/ interface=org.freedesktop.DBus.ObjectManager member=GetManagedObjects
	bluetoothd->>bluetoothctl: method return, array [???]

	bluetoothctl->>bluetoothd: 8. destination=org.freedesktop.DBus serial=8 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.AgentManager1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 9. destination=(null destination) serial=9 path=/ interface=org.freedesktop.DBus.ObjectManager member=InterfacesAdded<br>   object path "/org/bluez/agent"<br>array [???]

	bluetoothctl->>bluetoothd: 10. destination=org.bluez serial=10 path=/org/bluez interface=org.bluez.AgentManager1 member=RegisterAgent<br>object path "/org/bluez/agent"<br>string ""
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 11. destination=org.freedesktop.DBus serial=11 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.ProfileManager1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 12. destination=org.freedesktop.DBus serial=12 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Adapter1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 13. destination=org.freedesktop.DBus serial=13 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.GattManager1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 14. destination=org.freedesktop.DBus serial=14 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.LEAdvertisingManager1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 15. destination=org.freedesktop.DBus serial=15 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Media1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 16. destination=org.freedesktop.DBus serial=16 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.NetworkServer1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 17. destination=org.freedesktop.DBus serial=17 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0/dev_E4_5F_01_91_E9_EB',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Device1'"
	bluetoothd->>bluetoothctl: method return,

	bluetoothctl->>bluetoothd: 18. destination=org.freedesktop.DBus serial=18 path=/org/freedesktop/DBus interface=org.freedesktop.DBus member=AddMatch<br>string "type='signal',sender='org.bluez',path='/org/bluez/hci0/dev_90_E8_68_85_9A_08',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Device1'"
	bluetoothd->>bluetoothctl: method return,


```

#### - 1 Hello

```bash
method call time=1662016254.741639 sender=:1.268 -> destination=org.freedesktop.DBus serial=1 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=Hello
method return time=1662016254.741655 sender=org.freedesktop.DBus -> destination=:1.268 serial=1 reply_serial=1
   string ":1.268"
 
signal time=1662016254.741658 sender=org.freedesktop.DBus -> destination=(null destination) serial=251 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
   string ":1.268"
   string ""
   string ":1.268"

signal time=1662016254.741663 sender=org.freedesktop.DBus -> destination=:1.268 serial=2 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameAcquired
   string ":1.268"
```

#### - 2 AddMatch / NameOwnerChanged

```bash
method call time=1662016254.741826 sender=:1.268 -> destination=org.freedesktop.DBus serial=2 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.freedesktop.DBus',path='/org/freedesktop/DBus',interface='org.freedesktop.DBus',member='NameOwnerChanged',arg0='org.bluez'"
method return time=1662016254.741837 sender=org.freedesktop.DBus -> destination=:1.268 serial=3 reply_serial=2

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.freedesktop.DBus',path='/org/freedesktop/DBus',interface='org.freedesktop.DBus',member='NameOwnerChanged',arg0='org.bluez'\"
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### - 3 GetNameOwner

```bash
method call time=1662016254.742007 sender=:1.268 -> destination=org.freedesktop.DBus serial=3 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=GetNameOwner
   string "org.bluez"
method return time=1662016254.742020 sender=org.freedesktop.DBus -> destination=:1.268 serial=4 reply_serial=3
   string ":1.135"

```

```bash
export BLUEZX_COMMAND="\"org.bluez\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="GetNameOwner"

```

#### - 4 AddMatch / InterfacesAdded

```bash
method call time=1662016254.742022 sender=:1.268 -> destination=org.freedesktop.DBus serial=4 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesAdded'"
method return time=1662016254.742025 sender=org.freedesktop.DBus -> destination=:1.268 serial=5 reply_serial=4

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesAdded'\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### - 5 AddMatch / InterfacesRemoved

```bash
method call time=1662016254.742047 sender=:1.268 -> destination=org.freedesktop.DBus serial=5 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesRemoved'"
method return time=1662016254.742050 sender=org.freedesktop.DBus -> destination=:1.268 serial=6 reply_serial=5

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.bluez',path='/',interface='org.freedesktop.DBus.ObjectManager',member='InterfacesRemoved'\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### - 6 AddMatch / 

```bash
method call time=1662016254.742231 sender=:1.268 -> destination=org.freedesktop.DBus serial=6 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path_namespace='/org/bluez'"
method return time=1662016254.742260 sender=org.freedesktop.DBus -> destination=:1.268 serial=7 reply_serial=6

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.bluez',path_namespace='/org/bluez'\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### -  7 GetManagedObjects / 

```bash
method call time=1662016254.742262 sender=:1.268 -> destination=org.bluez serial=7 path=/; interface=org.freedesktop.DBus.ObjectManager; member=GetManagedObjects
method return time=1662016254.742651 sender=:1.135 -> destination=:1.268 serial=336 reply_serial=7
   array [
      dict entry(
         object path "/org/bluez"
         array [
            dict entry(
               string "org.freedesktop.DBus.Introspectable"
               array [
               ]
            )
            dict entry(
               string "org.bluez.AgentManager1"
               array [
               ]
            )
            dict entry(
               string "org.bluez.ProfileManager1"
               array [
               ]
            )
         ]
      )
      dict entry(
         object path "/org/bluez/hci0"
         array [
            dict entry(
               string "org.freedesktop.DBus.Introspectable"
               array [
               ]
            )
            dict entry(
               string "org.bluez.Adapter1"
               array [
                  dict entry(
                     string "Address"
                     variant                         string "00:15:83:E7:F1:21"
                  )
                  dict entry(
                     string "AddressType"
                     variant                         string "public"
                  )
                  dict entry(
                     string "Name"
                     variant                         string "msi-vbx"
                  )
                  dict entry(
                     string "Alias"
                     variant                         string "GATEUP-E7F121"
                  )
                  dict entry(
                     string "Class"
                     variant                         uint32 1835008
                  )
                  dict entry(
                     string "Powered"
                     variant                         boolean true
                  )
                  dict entry(
                     string "Discoverable"
                     variant                         boolean true
                  )
                  dict entry(
                     string "DiscoverableTimeout"
                     variant                         uint32 0
                  )
                  dict entry(
                     string "Pairable"
                     variant                         boolean false
                  )
                  dict entry(
                     string "PairableTimeout"
                     variant                         uint32 0
                  )
                  dict entry(
                     string "Discovering"
                     variant                         boolean false
                  )
                  dict entry(
                     string "UUIDs"
                     variant                         array [
                           string "00001133-0000-1000-8000-00805f9b34fb"
                           string "0000110e-0000-1000-8000-00805f9b34fb"
                           string "00001105-0000-1000-8000-00805f9b34fb"
                           string "00001132-0000-1000-8000-00805f9b34fb"
                           string "00001104-0000-1000-8000-00805f9b34fb"
                           string "00001200-0000-1000-8000-00805f9b34fb"
                           string "00005005-0000-1000-8000-0002ee000001"
                           string "00001112-0000-1000-8000-00805f9b34fb"
                           string "00001108-0000-1000-8000-00805f9b34fb"
                           string "0000110c-0000-1000-8000-00805f9b34fb"
                           string "00001801-0000-1000-8000-00805f9b34fb"
                           string "0000112f-0000-1000-8000-00805f9b34fb"
                           string "0000110b-0000-1000-8000-00805f9b34fb"
                           string "00001800-0000-1000-8000-00805f9b34fb"
                           string "0000110a-0000-1000-8000-00805f9b34fb"
                           string "00001106-0000-1000-8000-00805f9b34fb"
                        ]
                  )
                  dict entry(
                     string "Modalias"
                     variant                         string "usb:v1D6Bp0246d0535"
                  )
               ]
            )
            dict entry(
               string "org.freedesktop.DBus.Properties"
               array [
               ]
            )
            dict entry(
               string "org.bluez.GattManager1"
               array [
               ]
            )
            dict entry(
               string "org.bluez.LEAdvertisingManager1"
               array [
                  dict entry(
                     string "ActiveInstances"
                     variant                         byte 0
                  )
                  dict entry(
                     string "SupportedInstances"
                     variant                         byte 5
                  )
                  dict entry(
                     string "SupportedIncludes"
                     variant                         array [
                           string "tx-power"
                           string "appearance"
                           string "local-name"
                        ]
                  )
               ]
            )
            dict entry(
               string "org.bluez.Media1"
               array [
               ]
            )
            dict entry(
               string "org.bluez.NetworkServer1"
               array [
               ]
            )
         ]
      )
      dict entry(
         object path "/org/bluez/hci0/dev_E4_5F_01_91_E9_EB"
         array [
            dict entry(
               string "org.freedesktop.DBus.Introspectable"
               array [
               ]
            )
            dict entry(
               string "org.bluez.Device1"
               array [
                  dict entry(
                     string "Address"
                     variant                         string "E4:5F:01:91:E9:EB"
                  )
                  dict entry(
                     string "AddressType"
                     variant                         string "public"
                  )
                  dict entry(
                     string "Name"
                     variant                         string "umt-pi-4"
                  )
                  dict entry(
                     string "Alias"
                     variant                         string "umt-pi-4"
                  )
                  dict entry(
                     string "Class"
                     variant                         uint32 786432
                  )
                  dict entry(
                     string "Paired"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Trusted"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Blocked"
                     variant                         boolean false
                  )
                  dict entry(
                     string "LegacyPairing"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Connected"
                     variant                         boolean false
                  )
                  dict entry(
                     string "UUIDs"
                     variant                         array [
                           string "00001800-0000-1000-8000-00805f9b34fb"
                           string "00001801-0000-1000-8000-00805f9b34fb"
                        ]
                  )
                  dict entry(
                     string "Modalias"
                     variant                         string "usb:v1D6Bp0246d0532"
                  )
                  dict entry(
                     string "Adapter"
                     variant                         object path "/org/bluez/hci0"
                  )
                  dict entry(
                     string "ServicesResolved"
                     variant                         boolean false
                  )
               ]
            )
            dict entry(
               string "org.freedesktop.DBus.Properties"
               array [
               ]
            )
         ]
      )
      dict entry(
         object path "/org/bluez/hci0/dev_90_E8_68_85_9A_08"
         array [
            dict entry(
               string "org.freedesktop.DBus.Introspectable"
               array [
               ]
            )
            dict entry(
               string "org.bluez.Device1"
               array [
                  dict entry(
                     string "Address"
                     variant                         string "90:E8:68:85:9A:08"
                  )
                  dict entry(
                     string "AddressType"
                     variant                         string "public"
                  )
                  dict entry(
                     string "Name"
                     variant                         string "BC6669"
                  )
                  dict entry(
                     string "Alias"
                     variant                         string "BC6669"
                  )
                  dict entry(
                     string "Class"
                     variant                         uint32 2097152
                  )
                  dict entry(
                     string "Paired"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Trusted"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Blocked"
                     variant                         boolean false
                  )
                  dict entry(
                     string "LegacyPairing"
                     variant                         boolean false
                  )
                  dict entry(
                     string "Connected"
                     variant                         boolean false
                  )
                  dict entry(
                     string "UUIDs"
                     variant                         array [
                           string "00001800-0000-1000-8000-00805f9b34fb"
                           string "00001801-0000-1000-8000-00805f9b34fb"
                           string "0000180a-0000-1000-8000-00805f9b34fb"
                           string "0000ffff-0000-1000-8000-00805f9b34fb"
                        ]
                  )
                  dict entry(
                     string "Modalias"
                     variant                         string "usb:v1D6Bp0246d0538"
                  )
                  dict entry(
                     string "Adapter"
                     variant                         object path "/org/bluez/hci0"
                  )
                  dict entry(
                     string "ServicesResolved"
                     variant                         boolean false
                  )
               ]
            )
            dict entry(
               string "org.freedesktop.DBus.Properties"
               array [
               ]
            )
         ]
      )
   ]
```

```bash
export BLUEZX_COMMAND=""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/"
export DBUS_DEST_XXX="org.bluez"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus.ObjectManager"
export DBUS_METHOD_XXX="GetManagedObjects"

```

#### -  8 AddMatch / PropertiesChanged

```bash
method call time=1662016254.743054 sender=:1.268 -> destination=org.freedesktop.DBus serial=8 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.AgentManager1'"
method return time=1662016254.743059 sender=org.freedesktop.DBus -> destination=:1.268 serial=8 reply_serial=8

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.AgentManager1'\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### -  9 InterfacesAdded / 

```bash
signal time=1662016254.743450 sender=:1.268 -> destination=(null destination) serial=9 path=/; interface=org.freedesktop.DBus.ObjectManager; member=InterfacesAdded
   object path "/org/bluez/agent"
   array [
      dict entry(
         string "org.freedesktop.DBus.Introspectable"
         array [
         ]
      )
      dict entry(
         string "org.bluez.Agent1"
         array [
         ]
      )
   ]
```

```bash
export BLUEZX_COMMAND="\"{'org.freedesktop.DBus.Introspectable':'[]','org.bluez.Agent1':'[]'}\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH="/org/bluez/agent"

export DBUS_PATH_XXX="/"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX="org.freedesktop.DBus.ObjectManager"
export DBUS_S_NAME_XXX="InterfacesAdded"

export DBUS_M_IFAC_XXX=""
export DBUS_METHOD_XXX=""

```

#### -  10 RegisterAgent / 

```
method call time=1662016254.743481 sender=:1.268 -> destination=org.bluez serial=10 path=/org/bluez; interface=org.bluez.AgentManager1; member=RegisterAgent
   object path "/org/bluez/agent"
   string ""
method return time=1662016254.743675 sender=:1.135 -> destination=:1.268 serial=338 reply_serial=10

```

```bash
export BLUEZX_COMMAND="\"\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH="/org/bluez/agent"

export DBUS_PATH_XXX="/org/bluez"
export DBUS_DEST_XXX="org.bluez"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.bluez.AgentManager1"
export DBUS_METHOD_XXX="RegisterAgent"

```

#### -  11 AddMatch / PropertiesChanged

```bash
method call time=1662016254.743485 sender=:1.268 -> destination=org.freedesktop.DBus serial=11 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.ProfileManager1'"
method return time=1662016254.743488 sender=org.freedesktop.DBus -> destination=:1.268 serial=9 reply_serial=11

```

```bash
export BLUEZX_COMMAND="\"type='signal',sender='org.bluez',path='/org/bluez',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.ProfileManager1'\""
export BLUEZX_STRING="$BLUEZX_COMMAND"
export BLUEZX_ARRAY=""
export BLUEZX_DICT=""

export BLUEZX_OBJPATH=""

export DBUS_PATH_XXX="/org/freedesktop/DBus"
export DBUS_DEST_XXX="org.freedesktop.DBus"

export DBUS_S_IFAC_XXX=""
export DBUS_S_NAME_XXX=""

export DBUS_M_IFAC_XXX="org.freedesktop.DBus"
export DBUS_METHOD_XXX="AddMatch"

```

#### -  12 AddMatch/ PropertiesChanged

```bash
method call time=1662016254.743490 sender=:1.268 -> destination=org.freedesktop.DBus serial=12 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Adapter1'"
method return time=1662016254.743492 sender=org.freedesktop.DBus -> destination=:1.268 serial=10 reply_serial=12

```

#### -  13 AddMatch / PropertiesChanged

```bash
method call time=1662016254.743685 sender=:1.268 -> destination=org.freedesktop.DBus serial=13 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.GattManager1'"
method return time=1662016254.743689 sender=org.freedesktop.DBus -> destination=:1.268 serial=11 reply_serial=13

```

#### -  14 AddMatch / PropertiesChanged

```bash
method call time=1662016254.743869 sender=:1.268 -> destination=org.freedesktop.DBus serial=14 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.LEAdvertisingManager1'"
method return time=1662016254.743873 sender=org.freedesktop.DBus -> destination=:1.268 serial=12 reply_serial=14

```

#### - 15 AddMatch / PropertiesChanged

```bash
method call time=1662016254.744055 sender=:1.268 -> destination=org.freedesktop.DBus serial=15 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Media1'"
method return time=1662016254.744081 sender=org.freedesktop.DBus -> destination=:1.268 serial=13 reply_serial=15

```

#### - 16 AddMatch / PropertiesChanged

```bash
method call time=1662016254.744083 sender=:1.268 -> destination=org.freedesktop.DBus serial=16 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.NetworkServer1'"
method return time=1662016254.744086 sender=org.freedesktop.DBus -> destination=:1.268 serial=14 reply_serial=16

```

#### - 17 AddMatch / PropertiesChanged

```bash
method call time=1662016254.744094 sender=:1.268 -> destination=org.freedesktop.DBus serial=17 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0/dev_E4_5F_01_91_E9_EB',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Device1'"
method return time=1662016254.744097 sender=org.freedesktop.DBus -> destination=:1.268 serial=15 reply_serial=17

```

#### - 18 AddMatch / PropertiesChanged

```bash
method call time=1662016254.744194 sender=:1.268 -> destination=org.freedesktop.DBus serial=18 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=AddMatch
   string "type='signal',sender='org.bluez',path='/org/bluez/hci0/dev_90_E8_68_85_9A_08',interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',arg0='org.bluez.Device1'"
method return time=1662016254.744202 sender=org.freedesktop.DBus -> destination=:1.268 serial=16 reply_serial=18

````

# 