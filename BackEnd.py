import serial
import time

serial_port = '/dev/ttyACM0'
baud_rate = 9600

ser = None

# Variáveis para armazenamento dos dados de pressão
pressao = None

try:
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    print("Conexão estabelecida com o Arduino!")

    while True:
        if ser.in_waiting > 0:
            time.sleep(5)
            data = ser.readline().decode('utf-8').strip()

            if "Pressao:" in data:
                pressao = float(data.split(":")[1].strip())
            
            if pressao is not None:
                print(f"Pressão: {pressao} hPa")
            

except serial.SerialException:
    print("Não foi possível conectar ao Arduino.")
finally:
    if ser and ser.is_open:
        ser.close()
        print("Conexão serial fechada.")