package com.estgp.bot.georeferencedwikipediamap.maps_services;

import android.os.StrictMode;

import com.estgp.bot.georeferencedwikipediamap.GeoNames;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class GeoNamesHttpClient {
    /**
     * Esta classe serve para fazer o pedido à API da GeoNames
     * e obter os dados retornados do pedido JSON
     *
     * BASE_URL URL base para a API
     * USERNAME Username registado pata o uso da API
     * poi Instância da classe GeoNames, onde são guardados os POIs
     */

    private static String BASE_URL = "http://api.geonames.org/findNearbyPOIsOSMJSON?";
    private static String USERNAME = "&username=b0tass";
    private GeoNames poi = null;

    public GeoNames getGeoNamesData(String lat, String lng) {
        /**
         * Aqui é executado o pedido à API da GeoNames
         * através dos argumentos 'lat' e 'lng' são devolvidos os
         * POI existentes na próximidade geográfica, este método
         * faz o pedido e envia o resultado para a classe JSONGeoNamesParcer
         * onde a resposta é processada
         *
         * @param parser JSONGeoNamesParser, onde se vai guardar o JSONObject json com o conteúdo da resposta
         * @param con  HttpURLConnection, serve para establecer a ligação
         * @param is InputStream, usado para ler  a resposta
         * @param args String com os argumentos 'lat' e 'lng'
         *
         * @return poi, classe GeoNames com os dados lidos
         */
        JSONGeoNamesParser parser;
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        HttpURLConnection con = null;
        InputStream is = null;
        String args = "lat=" + lat + "&lng=" + lng;
        try {
            String urlString = BASE_URL + args + USERNAME;
            URL url = new URL(urlString);
            con = (HttpURLConnection) url.openConnection();
            con.setReadTimeout(100000);
            con.setConnectTimeout(100000);
            con.setRequestMethod("GET");
            con.setDoInput(true);
            con.connect();

            StringBuffer buffer = new StringBuffer();
            is = con.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String line = null;
            while ((line = br.readLine()) != null)
                buffer.append(line + "\r\n");
            is.close();
            JSONObject json = new JSONObject(buffer.toString());
            parser = new JSONGeoNamesParser();
            poi = new GeoNames();
            poi = parser.parse(json);
            con.disconnect();

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
            } catch (Throwable t) {
            }
            try {
                con.disconnect();
            } catch (Throwable t) {
            }
        }
        return poi;
    }
}