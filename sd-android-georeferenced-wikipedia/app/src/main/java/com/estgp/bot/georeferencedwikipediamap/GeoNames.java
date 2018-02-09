package com.estgp.bot.georeferencedwikipediamap;

public class GeoNames {
    /**
     * Classe onde são definidas variáveis, getters, setters e um array multidimensional
     * para o tratamento dos dados recebidos através do GeoNames
     *
     * name String, onde é guardado o último nome obtido pela API
     * lng String, onde é guardado a última longitude obtida pela API
     * lat String, onde é guardado a última latitude obtida pela API
     * poi_arr[][] Array multidimensional de Strings, onde são guardados todos os POIs devolvidos pela API
     */

    private String name;
    private String lng;
    private String lat;
    private String[][] poi_arr;

    public String getName() {
        /**
         * Método getName
         * Retorna o último nome obtido
         */
        return name;
    }

    public void setName(String name) {
        /**
         * Método setName
         * Recebe uma String e atribui-a  a 'name'
         */
        this.name = name;
    }

    public String getLng() {
        /**
         * Método getLng
         * Retorna a última longitude obtida
         */
        return lng;
    }

    public void setLng(String lng) {
        /**
         * Método setLng
         * Recebe uma String e atribui-a a 'lng'
         */
        this.lng = lng;
    }

    public String getLat() {
        /**
         * Método getLat
         * Retorna a última latitude obtida
         */
        return lat;
    }

    public void setLat(String lat) {
        /**
         * Método setLat
         * Recebe uma String e atribui-a a 'lat'
         */
        this.lat = lat;
    }

    public void makeArray(int len) {
        /**
         * Método makeArray
         * Recebe o tamanho do JSONArray recebido
         * e cria 'poi_arr' considerando esse valor
         */
        poi_arr = new String[len][3];
    }

    public String[][] getArray() {
        /**
         * Método getArray
         * Devolve o Array multidimensional 'poi_arr[][]'
         */
        return poi_arr;
    }

    public void setArray(int poi_no) {
        /**
         * Método setArray
         * Atribui os valores de referencia para os POIs às 3 dimenções definidas para esse efeito
         * Cada POI é colocado num índice de acordo com o valor recebido 'poi_no'
         *
         * @param poi_no Int, correspondente ao índice de cada POI
         */
        poi_arr[poi_no][0] = name;
        poi_arr[poi_no][1] = lng;
        poi_arr[poi_no][2] = lat;
    }
}