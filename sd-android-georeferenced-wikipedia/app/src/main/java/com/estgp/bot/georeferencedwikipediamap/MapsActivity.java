package com.estgp.bot.georeferencedwikipediamap;

import android.Manifest;
import android.app.Dialog;
import android.content.Intent;
import android.content.IntentSender;
import android.content.pm.PackageManager;
import android.location.Location;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.FragmentActivity;
import android.support.v4.content.ContextCompat;
import android.view.View;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import com.estgp.bot.georeferencedwikipediamap.maps_services.GeoNamesHttpClient;

/**
 * <h1>Georeferenced Wikipedia Map</h1>
 * Este programa foi desenvolvido no âmbito da cadeira de Sistemas Distribuidos
 * É uma aplicação Android consumidora dos serviços REST da Geonames e da OpenWeatherMap
 * Permite a visualização de um mapa populado por marcadores obtidos através da API da GeoNames
 * referentes a POIs
 * e também mostra o estado do tempo na posição atual considerando os dados obtidos pelo OpenWeatherMap
 *
 * @author Luis Carvalho
 * @version 1.0
 */
public class MapsActivity extends FragmentActivity implements OnMapReadyCallback, GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener, GoogleMap.OnCameraIdleListener {
    /**
     * Esta classe diz respeito à primeira atividade mostrada ao utilizador
     * consiste no uso da API do Google Maps para o desenho do mapa
     * e da API da GeoNames para obter os marcadores
     *
     * FINE_LOCATION_PERMISSION_REQUEST Variável que guarda o estado de acesso ás permissões de localização
     * CONNECTION_RESOLUTION_REQUEST  Variável que guarda o estado de acesso ás permissões de ligação
     * mGoogleApiClient Objeto cliente para o acesso às APIs da Google
     * mLastLocation Localização, guarda os dados da última llocalização cedidos pela API da Google
     * mMap Objeto que contém o mapa
     * geonamesdata Instância da classe GeoNames
     * geonames_client Instância da classe GeoNamesHttpClient
     */

    private static final int FINE_LOCATION_PERMISSION_REQUEST = 1;
    private static final int CONNECTION_RESOLUTION_REQUEST = 2;
    private GoogleApiClient mGoogleApiClient;
    private Location mLastLocation;
    private GoogleMap mMap;

    private GeoNames geonamesdata = null;
    private GeoNamesHttpClient geonames_client = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        /**
         * Método onde é inicializada a atividade inicial da aplicação
         *
         * @param savedInstanceState Variável que guarda o último estado da aplicação
         */

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);

        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

        buildGoogleAPIClient();
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        /**
         * Método que espera o evento de geração do mapa
         *e inicia o Listener para o movimento da câmera
         *
         * @param mMap Variável que guarda o mapa gerado
         */

        mMap = googleMap;
        mMap.setOnCameraIdleListener(this);
    }

    @Override
    protected void onStart() {
        /**
         * Método executado no arranque da aplicação
         * efetua a ligação à API do Maps
         *
         * @param mGoogleApiClient.connect() Ligação como cliente à API
         */
        mGoogleApiClient.connect();
        super.onStart();
    }

    @Override
    protected void onResume() {
        /**
         * Método executado quando a aplicação é reaberta
         * efetua a ligação à API do Maps
         *
         * @param buildGoogleAPIClient() Ligação à API
         */
        super.onResume();

        buildGoogleAPIClient();
    }

    @Override
    protected void onStop() {
        /**
         * Método executado quando a aplicação é fechada
         * termina a ligação com a API do Maps
         *
         * @param mGoogleApiClient.disconnect() Ligação à API
         */
        mGoogleApiClient.disconnect();
        super.onStop();
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {
        /**
         * Método chamado quando a app deteta uma ligação à Internet
         *
         * @param findLocation() chamada ao método findLocation()
         */
        findLocation();
    }

    @Override
    public void onConnectionSuspended(int i) {
        /**
         * Método chamado quando a ligação à Internet é suspensa
         * Deve lançar uma notificação
         */
        Toast.makeText(this, "Connection suspended", Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onConnectionFailed(@NonNull final ConnectionResult connectionResult) {
        /**
         * Método chamado quando a app não consegue obter uma ligação à Internet
         * Procura problemas de resolução, tenta voltar a conectar com a API do Maps
         *
         */
        if (connectionResult.hasResolution()) {
            try {
                connectionResult.startResolutionForResult(this, CONNECTION_RESOLUTION_REQUEST);
            } catch (IntentSender.SendIntentException e) {
                // There was an error with the resolution intent. Try again.
                mGoogleApiClient.connect();
            }
        } else {
            Dialog dialog = GooglePlayServicesUtil.getErrorDialog(connectionResult.getErrorCode(), this, 1);
            dialog.show();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        /**
         * Método chamado quando a app retorna da segunda atividade
         * Volta a ligar à API do Maps
         *
         */
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == CONNECTION_RESOLUTION_REQUEST && resultCode == RESULT_OK) {
            mGoogleApiClient.connect();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        /**
         * Método chamado quando obtém o input dos pedidos de permissões
         * Chama o método findLocation() em caso de sucesso
         *
         */
        switch (requestCode) {
            case FINE_LOCATION_PERMISSION_REQUEST: {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    findLocation();
                }
            }
        }
    }

    @Override
    public void onCameraIdle() {
        /**
         * Método chamado quando a câmera do mapa para de se mover
         * Chama o método getMarkers() e envia como argumento a posição atual da câmera num objeto LatLng
         *
         */
        getMarkers(mMap.getCameraPosition().target);
    }

    private void buildGoogleAPIClient() {
        /**
         * Método para construir a ligação com a API da Google
         * Caso não esteja instanciado, cria um novo
         */
        if (mGoogleApiClient == null) {
            mGoogleApiClient = new GoogleApiClient.Builder(this)
                    .addConnectionCallbacks(this)
                    .addOnConnectionFailedListener(this)
                    .addApi(LocationServices.API)
                    .build();
        }
    }

    public void changeType(View view) {
        /**
         * Método associado ao comportamento do botão 'MAP TYPE'
         * Altera o modo de visualização entre 'Normal' e 'Satélite'
         */
        if (mMap.getMapType() == GoogleMap.MAP_TYPE_NORMAL) {
            mMap.setMapType(GoogleMap.MAP_TYPE_SATELLITE);
        } else
            mMap.setMapType(GoogleMap.MAP_TYPE_NORMAL);
    }

    private void findLocation() {
        /**
         * Método que procura a localização atual, após verificar a existência das permissões
         * e coloca a câmera na posição recebida
         */
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, FINE_LOCATION_PERMISSION_REQUEST);
        } else {

            mMap.setMyLocationEnabled(true);

            mLastLocation = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);

            LatLng myLat = new LatLng(mLastLocation.getLatitude(), mLastLocation.getLongitude());
            mMap.moveCamera(CameraUpdateFactory.newLatLng(myLat));
            //getMarkers(myLat);
        }

    }

    private void getMarkers(LatLng center) {
        /**
         * Método responsável por colocar os marcadores recebidos no mapa
         * Através das coordenadas da posição atual da câmera do mapa
         * é feito um request à API do GeoNames que depois de processado
         * é devolvido sob um array multidimensional 'poi_arr' que é depois processado
         * de forma a obter os dados relevantes ao posicionamento e designação dos marcadores
         *
         * @param count Contador para efetuar a separação dos dados do array 'poi_arr'
         * @param c_lat String onde é guardada a latitude da posição central da câmera
         * @param c_lng String onde é guardada a longitude da posição central da câmera
         * @param geonamesdata Instância da classe GeoNames de onde se fazem os GETs aos dados
         * @param geonames_client Instância da classe GeoNamesHttpClient onde são feitos os pedidos à API da GeoNames
         * @param poi_arr[][] Array multidimensional de Strings, onde são interpretados os valores obtidos através da API
         */
        int count = 0;
        String c_lat, c_lng;

        geonamesdata = new GeoNames();
        geonames_client = new GeoNamesHttpClient();

        c_lat = String.valueOf(center.latitude);
        c_lng = String.valueOf(center.longitude);

        geonamesdata = geonames_client.getGeoNamesData(c_lat, c_lng);

        String[][] poi_arr = geonamesdata.getArray();
        String name = null, lng = null, lat = null;

        if (poi_arr != null) {
            for (int row = 0; row < poi_arr.length; row++) {
                for (int col = 0; col < poi_arr[row].length; col++) {
                    count++;
                    switch (count) {
                        case 1:
                            name = poi_arr[row][col];
                            break;
                        case 2:
                            lng = poi_arr[row][col];
                            break;
                        case 3:
                            lat = poi_arr[row][col];
                            count = 0;
                            LatLng marker = new LatLng(Double.parseDouble(lat), Double.parseDouble(lng));
                            mMap.addMarker(new MarkerOptions().position(marker).title(name));
                            break;
                    }
                }
            }
        } else {
            return;
        }
    }

    public void sendMessage(View view) {
        /**
         * Método chamado pelo evento OnClick do botão 'Weather'
         * guarda a localizção atual em duas variáveis, envia esses dados através de um Intent
         * para serem recebidos em WeatherActivity
         *
         * @param lat String, guarda a latitude atual
         * @param lon String, guarda a longitude atual
         */
        String lat, lon;
        Intent intent = new Intent(MapsActivity.this, WeatherActivity.class);

        lat = String.valueOf(mLastLocation.getLatitude());
        lon = String.valueOf(mLastLocation.getLongitude());
        intent.putExtra("last_lat", lat);
        intent.putExtra("last_lon", lon);
        startActivity(intent);
    }

}
