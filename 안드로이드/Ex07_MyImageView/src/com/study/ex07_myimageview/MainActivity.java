package com.study.ex07_myimageview;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ScrollView;

public class MainActivity extends Activity {

	ScrollView scrollView01;
	
	ImageView imageView01;
	ImageView imageView02;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		imageView01 = (ImageView)findViewById(R.id.imageView01);
		imageView02 = (ImageView)findViewById(R.id.imageView02);
		
		imageView01.setImageResource(R.drawable.background1);
		imageView02.setImageResource(0);
		
		imageView01.invalidate();
		imageView02.invalidate();
		
		
		scrollView01 = (ScrollView)findViewById(R.id.scrollView01);
		scrollView01.setVerticalScrollBarEnabled(true);
		scrollView01.setHorizontalFadingEdgeEnabled(true);
		
		Button btnDown = (Button)findViewById(R.id.button01);
		btnDown.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				imageDown();
			}
		});
		
		Button btnUp = (Button)findViewById(R.id.button02);
		btnUp.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				imageUp();
			}
		});
		
	}

	private void imageDown(){
		imageView01.setImageResource(0);
		imageView02.setImageResource(R.drawable.background1);
		
		imageView01.invalidate();
		imageView02.invalidate();
		
	}
	
	private void imageUp(){
		imageView01.setImageResource(R.drawable.background1);
		imageView02.setImageResource(0);
		
		imageView01.invalidate();
		imageView02.invalidate();
		
	}
}