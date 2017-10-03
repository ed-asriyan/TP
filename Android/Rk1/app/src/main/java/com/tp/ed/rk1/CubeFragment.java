package com.tp.ed.rk1;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;


public class CubeFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View root = inflater.inflate(R.layout.fragment_cube, container, false);

        root.findViewById(R.id.solver_cube).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                try {
                    double a = Double.parseDouble(((EditText) root.findViewById(R.id.a_cube)).getText().toString());
                    double b = Double.parseDouble(((EditText) root.findViewById(R.id.b_cube)).getText().toString());
                    double c = Double.parseDouble(((EditText) root.findViewById(R.id.c_cube)).getText().toString());

                    ((TextView) root.findViewById(R.id.result_cube)).setText(String.valueOf(solve(a, b, c)));
                } catch (NumberFormatException e) {
                    ((TextView) root.findViewById(R.id.result_cube)).setText(R.string.error);
                }
            }
        });
        return root;
    }

    private double solve(double a, double b, double c) {
        return a * b * c;
    }
}
