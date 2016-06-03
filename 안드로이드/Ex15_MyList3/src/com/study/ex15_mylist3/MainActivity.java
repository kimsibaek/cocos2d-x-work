package com.study.ex15_mylist3;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity extends Activity {

	String[] names = { "홍길동", "강감찬", "을지문덕", "양만춘", "유관순"};
	String[] ages = { "20", "25", "30", "35", "40"};
	int[] images = {R.drawable.face1, R.drawable.face2, R.drawable.face3, R.drawable.face1, R.drawable.face2};
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		//ArrayAdapter<String> adapter;
		//adapter = new ArrayAdapter<String> (this, android.R.layout.simple_list_item_1, names);
		
		
		
		final MyAdapter adapter = new MyAdapter();
		
		ListView listView1 = (ListView) findViewById(R.id.listView1);
		
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
			
			SingerItemView view = new SingerItemView(getApplicationContext());
			view.setName(names[position]);
			view.setAge(ages[position]);
			view.setImage(images[position]);
			
			return view;
		}
	}
	
	public boolean onCreateOptionsMenu(Menu menu){
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
}
