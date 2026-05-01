const API = 'http://localhost:8080/api';

// Affiche un message temporaire en bas a droite
function afficherMessage(texte, type) {
    const msg = document.getElementById('message');
    msg.textContent = texte;
    msg.className = type;
    setTimeout(() => { msg.className = ''; msg.style.display = 'none'; }, 3000);
}

// Interroge le serveur et met a jour l'affichage
async function rafraichir() {
    try {
        const res = await fetch(`${API}/etat`);
        const data = await res.json();
        afficherCaisses(data.caisses);
        document.getElementById('totalServis').textContent = data.totalServis;
    } catch (e) {
        console.error('Erreur connexion serveur', e);
    }
}

// Genere les cartes HTML a partir du tableau de caisses
function afficherCaisses(caisses) {
    const grille = document.getElementById('grille-caisses');
    grille.innerHTML = '';
    caisses.forEach(c => {
        const carte = document.createElement('div');
        carte.className = 'carte-caisse'
            + (c.express ? ' express' : '')
            + (c.ouverte ? '' : ' fermee');

        const statutBadge = c.ouverte 
            ? '<span class="badge ouverte">Ouverte</span>' 
            : '<span class="badge fermee">Fermée</span>';

        const expressBadge = c.express ? '<span class="badge express-tag">⭐ Express</span>' : '';

        const alerteHtml = c.nbClients > 5
            ? '<div class="alerte">⚠️ File surchargée</div>' : '';

        carte.innerHTML = `
            <div class="caisse-header">
                <h3>Caisse ${c.numero}</h3>
                ${expressBadge}
            </div>
            <div class="caisse-status" style="margin-bottom: 1rem;">
                ${statutBadge}
            </div>
            <div class="caisse-stats">
                <div class="stat-box">
                    <span class="val">${c.nbClients}</span>
                    <span class="lbl">Clients</span>
                </div>
                <div class="stat-box">
                    <span class="val">${c.tempsAttente}s</span>
                    <span class="lbl">Attente</span>
                </div>
            </div>
            ${alerteHtml}
        `;
        grille.appendChild(carte);
    });
}

// Ajouter un client
async function ajouterClient() {
    const nom = document.getElementById('nomClient').value.trim();
    const nb = parseInt(document.getElementById('nbArticles').value);

    if (!nom || isNaN(nb) || nb < 1) {
        afficherMessage('Remplis le nom et le nombre d\'articles !', 'erreur');
        return;
    }

    try {
        const res = await fetch(`${API}/client/ajouter`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ nom, nbArticles: nb })
        });
        const data = await res.json();
        if (data.erreur) {
            afficherMessage('Erreur : ' + data.erreur, 'erreur');
        } else {
            afficherMessage(`${nom} ajouté avec succès !`, 'succes');
            document.getElementById('nomClient').value = '';
            document.getElementById('nbArticles').value = '';
            rafraichir();
        }
    } catch (e) {
        afficherMessage('Erreur connexion serveur', 'erreur');
    }
}

// Servir un client
async function servirClient() {
    const numero = parseInt(document.getElementById('numeroCaisse').value);
    if (isNaN(numero)) {
        afficherMessage('Entre un numéro de caisse !', 'erreur');
        return;
    }
    try {
        const res = await fetch(`${API}/caisse/servir`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ numero })
        });
        const data = await res.json();
        if (data.erreur) {
            afficherMessage('Erreur : ' + data.erreur, 'erreur');
        } else {
            afficherMessage(`Client servi à la caisse ${numero} !`, 'succes');
            rafraichir();
        }
    } catch (e) {
        afficherMessage('Erreur connexion serveur', 'erreur');
    }
}

// Ouvrir une caisse
async function ouvrirCaisse() {
    const numero = parseInt(document.getElementById('numeroCaisse').value);
    if (isNaN(numero)) {
        afficherMessage('Entre un numéro de caisse !', 'erreur');
        return;
    }
    try {
        const res = await fetch(`${API}/caisse/ouvrir`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ numero })
        });
        const data = await res.json();
        if (data.erreur) {
            afficherMessage('Erreur : ' + data.erreur, 'erreur');
        } else {
            afficherMessage(`Caisse ${numero} ouverte !`, 'succes');
            rafraichir();
        }
    } catch (e) {
        afficherMessage('Erreur connexion serveur', 'erreur');
    }
}

// Fermer une caisse
async function fermerCaisse() {
    const numero = parseInt(document.getElementById('numeroCaisse').value);
    if (isNaN(numero)) {
        afficherMessage('Entre un numéro de caisse !', 'erreur');
        return;
    }
    try {
        const res = await fetch(`${API}/caisse/fermer`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ numero })
        });
        const data = await res.json();
        if (data.erreur) {
            afficherMessage('Erreur : ' + data.erreur, 'erreur');
        } else {
            afficherMessage(`Caisse ${numero} fermée !`, 'succes');
            rafraichir();
        }
    } catch (e) {
        afficherMessage('Erreur connexion serveur', 'erreur');
    }
}

// Rafraichissement automatique toutes les 3 secondes
setInterval(rafraichir, 3000);
rafraichir();