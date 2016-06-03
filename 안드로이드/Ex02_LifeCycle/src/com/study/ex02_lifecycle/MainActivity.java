package com.study.ex02_lifecycle;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		// 버튼5 :
		// 내가 생성한 액티비티 실행하고 결과 받아오기
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				Intent intent = new Intent(getApplicationContext(), NewActivity.class);
				intent.putExtra("CustomerName", "홍길동");
				//startActivity(intent);
				startActivityForResult(intent, 1);
			}
		});
	}

	
}
