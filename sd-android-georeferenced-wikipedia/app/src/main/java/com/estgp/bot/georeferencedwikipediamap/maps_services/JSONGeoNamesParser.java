package com.estgp.bot.georeferencedwikipediamap.maps_services;

import com.estgp.bot.georeferencedwikipediamap.GeoNames;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


public class JSONGeoNamesParser {
    /**
     * Classe encarregue de interpretar e selecionar os dados provenientes da resposta
     * guardada no JSONObject json
     *
     * poi Instância da classe GeoNames para onde os dados obtidos são enviados
     * parsed JSONArray onde os dados da resposta são copiados
     */
    private GeoNames poi = null;
    JSONArray parsed = null;

    public GeoNames parse(JSONObject json) throws JSONException {
        /**
         * Aqui procede-se ao tratamento dos dados provenientes da GeoNames
         * após se retirar o array da resposta este é lido e através das keys presentes
         * retiram-se os dados relevantes para a marcação dos Markers
         *
         * @param poi Intância da classe GeoNames para o envio dos dados processados
         * @param parsed JSONArray criado através da resposta segundo a key 'poi'
         */
        poi = new GeoNames();
        parsed = json.getJSONArray("poi");

        try {
            poi.makeArray(parsed.length());

            for (int i = 0; i < parsed.length(); i++) {
                JSONObject element = parsed.getJSONObject(i);

                if (element.get("name").equals("")) {
                    poi.setName(element.getString("typeName"));
                } else {
                    poi.setName(element.getString("name"));
                }

                poi.setLng(element.getString("lng"));
                poi.setLat(element.getString("lat"));

                poi.setArray(i);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return poi;
    }
}
