import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;

public class MyController implements Initializable {

	@FXML
	ListView<String> inventory, textView;
	
	@FXML
	Label healthLabel, levelLabel;
	
	SerialConnection serial;
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		serial = new SerialConnection();
	}
	
	

}
