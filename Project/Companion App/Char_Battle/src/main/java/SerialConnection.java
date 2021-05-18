import com.fazecast.jSerialComm.SerialPort;

public class SerialConnection {
	SerialPort conn;
	
	public SerialConnection() {
		conn = SerialPort.getCommPort("COM9");
		conn.setBaudRate(9600);
		
		if (!conn.openPort()) {
			System.out.println("port not open");
		}
	}
	
	public String read() {
		int len = conn.bytesAvailable();
		if (len > 0) {
			String s = "";
			byte[] buf = new byte[len];
			int bytesRead = conn.readBytes(buf, len);
			for (int i = 0; i < bytesRead; i++) {
				s += (char)buf[i];
			}
			return s;
		}
		return null;
	}
	
	public void write(String s) {
		byte[] buf = new byte[s.length()];
		for (int i = 0; i < s.length(); i++) {
			buf[i] = (byte)s.charAt(i);
		}
		conn.writeBytes(buf, s.length());
	}
}
