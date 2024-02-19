#!groovy

pipeline {
	agent any
	
	stages{
        stage('Docker Build') {
            steps {
                //git branch: 'main', credentialsId: 'github', url: 'git@github.com:packofviceroy/http_server.git/'
      	        sh 'docker build -t simplehttpsserver/latest .'
            }
        }
        stage('Docker Test'){
            steps{
                sh 'docker run -d simplehttpsserver/latest -p 8080:4337'
            }
        }
    }
}