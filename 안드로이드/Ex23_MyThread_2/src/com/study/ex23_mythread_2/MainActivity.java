package com.study.ex23_mythread_2;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MainActivity extends Activity {
	TextView textView1;
	Handler handler;
	ProgressBar progressBar1;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		handler = new Handler();
		
		textView1 = (TextView) findViewById(R.id.textView1);
		
		progressBar1 = (ProgressBar) findViewById(R.id.progressBar1);
		
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
				final int index = i;
				
				handler.post(new Runnable(){
					public void run(){
						textView1.setText("Request Thread .." + index);
						
						progressBar1.incrementProgressBy(1);
					}
					
				});
				
				try{
					Thread.sleep(500);
				}catch(InterruptedException e){
					e.printStackTrace();
				}
			}
		}
	}
}
