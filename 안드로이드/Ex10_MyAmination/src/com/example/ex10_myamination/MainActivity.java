package com.example.ex10_myamination;

import android.app.Activity;
import android.graphics.Matrix;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity {

	ImageView imageView1;
	
	int i = 0;
	float x = 0.0f;
	float y = 0.0f;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		imageView1 = (ImageView)findViewById(R.id.imageView1);
		
		final Animation anim1 = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.move);
		final Animation anim2 = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.size_change);
		final Animation anim3 = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.change_alpha);
		
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				imageView1.startAnimation(anim1);
			}
		});
		
		Button button2 = (Button)findViewById(R.id.button2);
		button2.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				imageView1.startAnimation(anim2);
			}
		});
		
		Button button3 = (Button)findViewById(R.id.button3);
		button3.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				imageView1.startAnimation(anim3);
			}
		});
		
		Button button4 = (Button)findViewById(R.id.button4);
		button4.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				i = 0;
				x=0.0f;
				y=0.0f;
				mHandler.sendEmptyMessage(0);
			}
		});
	}
	
	Handler mHandler = new Handler(){
		public void handleMessage(Message msg){
			Matrix matrix = new Matrix();
			x = x + 10.0f;
			y= y+ 10.0f;
			matrix.postTranslate(x, y);
			
			imageView1.setImageMatrix(matrix);
			
			Log.d("gikimi", "Timer:"+i);
			
			if( i< 20) {
				mHandler.sendEmptyMessageDelayed(0, 500);
			}
			i++;
		}
	};
}
