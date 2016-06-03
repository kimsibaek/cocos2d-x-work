package com.example.ex22_mythread_1;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView textView1;
	ProgressHandler handler;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		handler = new ProgressHandler();
		
		textView1 = (TextView) findViewById(R.id.textView1);
		
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener(){
			
			public void onClick(View v){
				RequestThread thread = new RequestThread();
				thread.start();
			}
		});
	}

	class RequestThread extends Thread{
		public void run(){
			for(int i=0; i<100; i++){
				Message msg = handler.obtainMessage();
				
				Bundle bundle = new Bundle();
				bundle.putString("data", "Request Thread .." + i);
				msg.setData(bundle);
				
				handler.sendMessage(msg);
				
				try{
					Thread.sleep(1000);
				}catch(InterruptedException e){
					e.printStackTrace();
				}
			}
		}
	}
	
	class ProgressHandler extends Handler{
		
		public void handleMessage(Message msg){
			Bundle bundle = msg.getData();
			String data = bundle.getString("data");
			
			textView1.setText(data);
		}
	}
}
