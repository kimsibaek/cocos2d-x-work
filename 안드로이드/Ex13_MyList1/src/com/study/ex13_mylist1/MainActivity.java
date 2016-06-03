package com.study.ex13_mylist1;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity extends Activity {

	String[] names = { "È«±æµ¿", "°­°¨Âù", "À»Áö¹®´ö", "¾ç¸¸Ãá", "À¯°ü¼ø", "È«±æµ¿", "°­°¨Âù", "À»Áö¹®´ö", "¾ç¸¸Ãá", "À¯°ü¼ø", "È«±æµ¿", "°­°¨Âù", "À»Áö¹®´ö", "¾ç¸¸Ãá", "À¯°ü¼ø", "È«±æµ¿", "°­°¨Âù", "À»Áö¹®´ö", "¾ç¸¸Ãá", "À¯°ü¼ø" };
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		ArrayAdapter<String> adapter;
		adapter = new ArrayAdapter<String> (this, android.R.layout.simple_list_item_1, names);
		
		ListView listView1 = (ListView) findViewById(R.id.listView1);
		
		listView1.setAdapter(adapter);
		
		listView1.setOnItemClickListener(new OnItemClickListener(){
			
			public void onItemClick(AdapterView<?> arg0, View arg1, int position, long arg3){
				Toast.makeText(getApplicationContext(), "selected : " + names[position], Toast.LENGTH_SHORT).show();
			}
		});
	}
}
