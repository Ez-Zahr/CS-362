import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class CharBattleGUI extends Application {
	
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setTitle("Char Battle");
		FXMLLoader loader = new FXMLLoader(getClass().getResource("CharScene.fxml"));
		
		Scene scene = new Scene(loader.load(), 700,450);
		primaryStage.setScene(scene);
		primaryStage.show();
	}

}
