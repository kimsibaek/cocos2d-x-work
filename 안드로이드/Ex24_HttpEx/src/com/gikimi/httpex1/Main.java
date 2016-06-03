package com.gikimi.httpex1;

import android.os.Bundle;
import android.app.Activity;
import android.content.*;
import android.view.*;
import android.view.View.*;
import android.widget.*;

public class Main extends Activity {

	Button 		btnGetAct;
	Button 		btnPostAct;

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        btnGetAct = (Button)findViewById(R.id.btnGetAct);
        btnGetAct.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent(Main.this, HttpGetTest.class);
		        startActivity(intent);
			}
		});

        btnPostAct = (Button)findViewById(R.id.btnPostAct);
        btnPostAct.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent(Main.this, HttpPostTest.class);
		        startActivity(intent);
			}
		});

	}

}
