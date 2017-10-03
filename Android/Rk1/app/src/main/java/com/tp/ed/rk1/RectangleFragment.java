package com.tp.ed.rk1;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

public class RectangleFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View root = inflater.inflate(R.layout.fragment_rectangle, container, false);

        root.findViewById(R.id.solver_rectangle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                try {
                    double a = Double.parseDouble(((EditText) root.findViewById(R.id.a_rectangle)).getText().toString());
                    double b = Double.parseDouble(((EditText) root.findViewById(R.id.b_rectangle)).getText().toString());

                    ((TextView) root.findViewById(R.id.result_rectangle)).setText(String.valueOf(solve(a, b)));
                } catch (NumberFormatException e) {
                    ((TextView) root.findViewById(R.id.result_rectangle)).setText(R.string.error);
                }
            }
        });
        return root;
    }

    private double solve(double a, double b) {
        return a * b;
    }
}
