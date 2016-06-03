package com.study.ex32_mysercvice;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class MyService1 extends Service {

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	public void onCreate(){
		super.onCreate();
		
		MyThread1 thread = new MyThread1();
		thread.start();
	}
	
	class MyThread1 extends Thread{
		public void run(){
			for(int i=0; i<1000; i++){
				Log.d("gikimi", "service called.. " + i);
				
				try{
					Thread.sleep(1000);
				}catch(InterruptedException e){
					e.printStackTrace();
				}
			}
		}
	}
	
	public void onDestroy(){
		super.onDestroy();
	}
}
