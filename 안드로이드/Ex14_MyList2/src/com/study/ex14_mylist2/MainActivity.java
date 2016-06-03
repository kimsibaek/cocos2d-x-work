package com.study.ex14_mylist2;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	String[] names = { "홍길동", "강감찬", "을지문덕", "양만춘", "유관순"};
	String[] ages = { "20", "25", "30", "35", "40"};
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		//ArrayAdapter<String> adapter;
		//adapter = new ArrayAdapter<String> (this, android.R.layout.simple_list_item_1, names);
		
		ListView listView1 = (ListView) findViewById(R.id.listView1);
		
		final MyAdapter adapter = new MyAdapter();
		
		listView1.setAdapter(adapter);
		
		listView1.setOnItemClickListener(new OnItemClickListener(){
			
			public void onItemClick(AdapterView<?> arg0, View arg1, int position, long arg3){
				Toast.makeText(getApplicationContext(), "selected : " + names[position], Toast.LENGTH_SHORT).show();
			}
		});
	}
	
	class MyAdapter extends BaseAdapter {
		
		public int getCount(){
			return names.length;
		}
		
		public Object getItem(int position){
			return names[position];
		}
		
		public long getItemId(int position){
			return position;
		}
		
		public View getView(int position, View convertView, ViewGroup parent){
			
			LinearLayout layout = new LinearLayout(getApplicationContext());
			layout.setOrientation(LinearLayout.VERTICAL);
			
			TextView view1 = new TextView(getApplicationContext());
			view1.setText(names[position]);
			view1.setTextSize(40.0f);
			view1.setTextColor(Color.BLUE);
			
			layout.addView(view1);
			
			TextView view2 = new TextView(getApplicationContext());
			view2.setText(ages[position]);
			view2.setTextSize(40.0f);
			view1.setTextColor(Color.RED);
			
			layout.addView(view2);
			
			return layout;
		}
	}
}
