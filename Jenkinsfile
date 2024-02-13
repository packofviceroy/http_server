#!groovy

pipeline {
	agent any
	
	stages{
        stage('Docker Build') {
            steps {
                git 'git@github.com:packofviceroy/http_server.git' 
      	        sh 'docker build -t simplehttpsserver/latest .'
            }
        }
    }
}